// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// vim:set sts=4 ts=8:

// Copyright (c) 2001-2005 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/bgp/bgp.cc,v 1.49 2005/01/31 23:14:47 pavlin Exp $"

// #define DEBUG_MAXIMUM_DELAY
// #define DEBUG_LOGGING
// #define DEBUG_PRINT_FUNCTION_NAME

#include <sys/time.h>

#include "config.h"
#include "bgp_module.h"

#include "libxorp/selector.hh"
#include "libxorp/xlog.h"

#include "bgp.hh"
#include "path_attribute.hh"
#include "iptuple.hh"
#include "xrl_target.hh"
#include "profile_vars.hh"

// ----------------------------------------------------------------------------
// Static class members

EventLoop BGPMain::_eventloop;

// ----------------------------------------------------------------------------
// BGPMain implementation

BGPMain::BGPMain()
    : _exit_loop(false)
{
    debug_msg("BGPMain object created\n");
    /*
    ** Ideally these data structures should be created inline. However
    ** we need to finely control the order of destruction.
    */
    _peerlist = new BGPPeerList();
    _xrl_router = new XrlStdRouter(eventloop(), "bgp");
    _xrl_target = new XrlBgpTarget(_xrl_router, *this);

    wait_until_xrl_router_is_ready(eventloop(), *_xrl_router);

    _rib_ipc_handler = new RibIpcHandler(*_xrl_router, *this);
    _next_hop_resolver_ipv4 = new NextHopResolver<IPv4>(_xrl_router,
							eventloop(),
							*this);
    _next_hop_resolver_ipv6 = new NextHopResolver<IPv6>(_xrl_router,
							eventloop(),
							*this);
    _plumbing_unicast = new BGPPlumbing(SAFI_UNICAST,
					_rib_ipc_handler,
					*_next_hop_resolver_ipv4,
					*_next_hop_resolver_ipv6,
					_policy_filters,
					*this);
    _plumbing_multicast = new BGPPlumbing(SAFI_MULTICAST,
					  _rib_ipc_handler,
					  *_next_hop_resolver_ipv4,
					  *_next_hop_resolver_ipv6,
					  _policy_filters,
					  *this);
    _rib_ipc_handler->set_plumbing(_plumbing_unicast, _plumbing_multicast);

    _process_watch = new ProcessWatch(_xrl_router, eventloop(),
				      bgp_mib_name().c_str(),
				      ::callback(this,
						 &BGPMain::terminate));

    initialize_profiling_variables(_profile);
}

BGPMain::~BGPMain()
{
    /*
    ** Stop accepting network connections.
    */
    stop_all_servers();

    debug_msg("-------------------------------------------\n");
    debug_msg("Stopping All Peers\n");
    _peerlist->all_stop();

    debug_msg("-------------------------------------------\n");
    debug_msg("Waiting for all peers to go to idle\n");
    while (_peerlist->not_all_idle() || _rib_ipc_handler->busy() ||
	   DeleteAllNodes<IPv4>::running() || 
	   DeleteAllNodes<IPv6>::running()) {
	eventloop().run();
    }
    /*
    ** NOTE: We expect one timer to be pending. The timer is in the xrl_router.
    */
    if (eventloop().timer_list_length() > 1)
	XLOG_INFO("EVENT: timers %u",
		  XORP_UINT_CAST(eventloop().timer_list_length()));

    /*
    ** Force the table de-registration from the RIB. Otherwise the
    ** destructor for the rib_ipc_handler will complain.
    */
    _rib_ipc_handler->register_ribname("");

    bool message = false;
    while(_xrl_router->pending()) {
	eventloop().run();
	if (!message) {
	    XLOG_INFO("xrl router still has pending operations");
	    message = true;
	}
    }

    if (message) {
	XLOG_INFO("xrl router no more pending operations");
    }

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting rib_ipc_handler\n");
    delete _rib_ipc_handler;

    message = false;
    while(_xrl_router->pending()) {
	eventloop().run();
	if (!message) {
	    XLOG_INFO("xrl router still has pending operations");
	    message = true;
	}
    }

    if (message) {
	XLOG_INFO("xrl router no more pending operations");
    }

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting Xrl Target\n");
    delete _xrl_target;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting xrl_router\n");
    delete _xrl_router;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting peerlist\n");
    delete _peerlist;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting plumbing unicast\n");
    delete _plumbing_unicast;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting plumbing multicast\n");
    delete _plumbing_multicast;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting next hop resolver IPv4\n");
    delete _next_hop_resolver_ipv4;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting next hop resolver IPv6\n");
    delete _next_hop_resolver_ipv6;

    debug_msg("-------------------------------------------\n");
    debug_msg("Deleting process watcher\n");
    delete _process_watch;

    debug_msg("-------------------------------------------\n");
    debug_msg("Delete BGPMain complete\n");
    debug_msg("-------------------------------------------\n");
}

ProcessStatus
BGPMain::status(string& reason)
{
    ProcessStatus s = PROC_READY;
    reason = "Ready";

    if (_plumbing_unicast->status(reason) == false ||
	_plumbing_multicast->status(reason) == false) {
	s = PROC_FAILED;
    } else if (_exit_loop == true) {
	s = PROC_SHUTDOWN;
	reason = "Shutting Down";
    }

    return s;
}

#ifdef	DEBUG_MAXIMUM_DELAY
#ifndef DEBUG_LOGGING
#error "Must use DEBUG_LOGGING in conjunction with DEBUG_MAXIMUM_DELAY"
#endif /* DEBUG_LOGGING */
inline
bool
check_callback_duration()
{
    static time_t last = time(0);
    static time_t largest = 0;
    time_t current = time(0);

    time_t diff	= current - last;
    debug_msg("current %ld largest %ld\n", diff, largest);
    last = current;
    largest = diff > largest ? diff : largest;

    return true;
}
#endif

void
BGPMain::main_loop()
{
    debug_msg("BGPMain::main_loop started\n");

#if defined(DEBUG_MAXIMUM_DELAY)
    static XorpTimer t = eventloop().
	new_periodic(1000, callback(check_callback_duration));
#endif
    while ( run() ) {
#if defined(DEBUG_MAXIMUM_DELAY)
	static time_t last = 0;
	time_t current = time(0);
	char* date = ctime(&current);
	debug_msg("Eventloop: %.*s, %ld\n",
		  static_cast<char>(strlen(date) - 1), date,
		  current - last);
#endif

	eventloop().run();
#if defined (DEBUG_MAXIMUM_DELAY)
	last = current;;
#endif
    }
#if defined(DEBUG_MAXIMUM_DELAY)
    t.unschedule();
#endif
}

void
BGPMain::local_config(const uint32_t& as, const IPv4& id)
{
    LocalData *local = get_local_data();

    local->set_as(AsNum(as));
    local->set_id(id);

    _plumbing_unicast->set_my_as_number(local->as());
    _plumbing_multicast->set_my_as_number(local->as());
}

/*
** Callback registered with the asyncio code.
*/
void
BGPMain::connect_attempt(int fd, SelectorMask m,
			 string laddr, uint16_t lport)
{
    if (SEL_RD != m) {
	XLOG_WARNING("Unexpected SelectorMask %#x", m);
	return;
    }

    char buf[Socket::SOCKET_BUFFER_SIZE];
    struct sockaddr *cliaddr = reinterpret_cast<struct sockaddr *>(buf);
    socklen_t clilen = sizeof(buf);

    int connfd = accept(fd, cliaddr, &clilen);

    debug_msg("Incoming connection attempt %d\n", connfd);

    if (-1 == connfd) {
	XLOG_WARNING("Accept failed %s", strerror(errno));
	return;
    }

    // Extract the peers IP address.
    char peername[1024];
    int error;
    if ((error = getnameinfo(cliaddr, clilen , peername, sizeof(peername),
			     0, 0, NI_NUMERICHOST)))
	XLOG_FATAL("getnameinfo() failed: %s", gai_strerror(error));

    /*
    ** Loop through our peer list and see if we are configured for
    ** this guy.
    */
    _peerlist->dump_list();

    list<BGPPeer *>& peers = _peerlist->get_list();
    list<BGPPeer *>::iterator i;

    for (i = peers.begin(); i != peers.end(); i++) {
	const Iptuple& iptuple = (*i)->peerdata()->iptuple();
	debug_msg("Trying: %s ", iptuple.str().c_str());

	if (iptuple.get_local_port() == lport &&
	   iptuple.get_local_addr() == laddr &&
	   iptuple.get_peer_addr() == peername) {
	    debug_msg(" Succeeded\n");
	    (*i)->connected(connfd);
	    return;
	}
	debug_msg(" Failed\n");
    }

    XLOG_WARNING("Connection by %s denied", peername);
    if (-1 == close(connfd))
	XLOG_WARNING("Close failed %s", strerror(errno));

    /*
    ** If at some later point in time we want to allow some form of
    ** promiscuous peering then enable this code.
    ** NOTE:
    ** The code below will allow an arbitary host to bring up a BGP
    ** session. If the peer tears down the session, the current code
    ** will attempt to re-establish contact. This is probably not what
    ** is wanted. The connect code requires
    ** _SocketClient->_Hostname to be set which it isn't. So expect a
    ** core dump. If we are supporting promiscuous peering maybe we
    ** never want to attempt to re-establish a connection. So don't
    ** bother to assign the hostname, just use it as a flag to totally
    ** drop the peering.
    */
#if	0
    // create new peer
    debug_msg("Creating new peer after socket connection\n");
    BGPPeer *peer = new BGPPeer(_localdata, new BGPPeerData, this, connfd);
    peer->event_open();
    add_peer(peer);
#endif
}

void
BGPMain::attach_peer(BGPPeer* peer)
{
    debug_msg("Peer added (fd %d)\n", peer->get_sock());
    _peerlist->add_peer(peer);
}

void
BGPMain::detach_peer(BGPPeer* peer)
{
    debug_msg("Peer removed (fd %d)\n", peer->get_sock());
    _peerlist->remove_peer(peer);
}

/*
** Find this peer if it exists.
*/
BGPPeer *
BGPMain::find_peer(const Iptuple& search)
{
    debug_msg("Searching for: %s\n", search.str().c_str());

    list<BGPPeer *>& peers = _peerlist->get_list();
    list<BGPPeer *>::iterator i;

    for (i = peers.begin(); i != peers.end(); i++) {
	const Iptuple& iptuple = (*i)->peerdata()->iptuple();
	debug_msg("Trying: %s ", iptuple.str().c_str());

	if (search == iptuple) {
	    debug_msg(" Succeeded\n");
	    return *i;
	}
	debug_msg(" Failed\n");
    }

    debug_msg("No match\n");

    return 0;
}

bool
BGPMain::create_peer(BGPPeerData *pd)
{
    debug_msg("Creating new Peer: %s\n",
	      pd->iptuple().str().c_str());
    debug_msg("Using local address %s for our nexthop\n",
	      pd->get_v4_local_addr().str().c_str());
    pd->dump_peer_data();

    /*
    ** Check that we don't already know about this peer.
    */
    if (find_peer(pd->iptuple())) {
	XLOG_WARNING("This peer already exists: %s %s",
		     pd->iptuple().str().c_str(),
		     pd->as().str().c_str());
	return false;
    }

    bool md5sig = !pd->get_md5_password().empty();

    SocketClient *sock = new SocketClient(pd->iptuple(), eventloop(), md5sig);

    BGPPeer *p = new BGPPeer(&_local_data, pd, sock, this);
    //    sock->set_eventloop(eventloop());
    sock->set_callback(callback(p, &BGPPeer::get_message));

    attach_peer(p);
//     p->event_start();

    return true;
}

bool
BGPMain::delete_peer(const Iptuple& iptuple)
{
    if (!disable_peer(iptuple))
	return false;

    /* XXX - Atanu
    **
    ** We would like to detach the peer from the peerlist at this
    ** point. However the call to disable_peer is not synchronous,
    ** it will cause a cease to be sent. We could set some state in
    ** the peer so that the when the cease is sent the peer can remove
    ** itself.
    **
    ** For the moment the peer is kept in the list.
    **
    */

    return true;
}

bool
BGPMain::enable_peer(const Iptuple& iptuple)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer->event_start();
    start_server(iptuple); // Start a server for this peer.
    peer->set_current_peer_state(true);
    return true;
}

bool
BGPMain::disable_peer(const Iptuple& iptuple)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer->event_stop();
    stop_server(iptuple); // Stop the server for this peer.
    peer->set_current_peer_state(false);
    return true;
}

bool
BGPMain::set_nexthop6(const Iptuple& iptuple, const IPv6& next_hop)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }
    const_cast<BGPPeerData*>(peer->peerdata())->set_v6_local_addr(next_hop);

    return true;
}

bool
BGPMain::get_nexthop6(const Iptuple& iptuple, IPv6& next_hop)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }
    next_hop = peer->peerdata()->get_v6_local_addr();

    return true;
}

bool
BGPMain::set_peer_state(const Iptuple& iptuple, bool state)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer->set_next_peer_state(state);

    if (false == peer->get_activate_state())
	return true;

    return activate(iptuple);
}

bool
BGPMain::set_peer_md5_password(const Iptuple& iptuple, const string& password)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == NULL) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    // The md5-password property has to belong to BGPPeerData, because
    // it is instantiated before BGPPeer and before SocketClient.
    BGPPeerData* pd = const_cast<BGPPeerData*>(peer->peerdata());
    pd->set_md5_password(password);

    return true;
}

bool
BGPMain::activate(const Iptuple& iptuple)
{
    BGPPeer *peer = find_peer(iptuple);

    if (peer == 0) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer->set_activate_state(true);

    if (peer->get_current_peer_state() == peer->get_next_peer_state())
	return true;

    if (peer->get_next_peer_state()) {
	enable_peer(iptuple);
    } else {
	disable_peer(iptuple);
    }

    return true;
}

bool
BGPMain::next_hop_rewrite_filter(const Iptuple& iptuple, const IPv4& next_hop)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    BGPPeerData* pd = const_cast<BGPPeerData*>(peer->peerdata());
    pd->set_next_hop_rewrite(next_hop);

    return true;
}

bool
BGPMain::get_peer_list_start(uint32_t& token)
{
    return _peerlist->get_peer_list_start(token);
}

bool
BGPMain::get_peer_list_next(const uint32_t& token,
			string& local_ip,
			uint32_t& local_port,
			string& peer_ip,
			uint32_t& peer_port)
{
    return _peerlist->get_peer_list_next(token, local_ip, local_port,
					 peer_ip, peer_port);
}

bool
BGPMain::get_peer_id(const Iptuple& iptuple, IPv4& peer_id)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer_id = peer->peerdata()->id();
    return true;
}

bool
BGPMain::get_peer_status(const Iptuple& iptuple,
			 uint32_t& peer_state,
			 uint32_t& admin_status)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer_state = peer->state();
    //XXX state stopped is only for our internal use.
    if (peer_state == STATESTOPPED)
	peer_state = STATEIDLE;

    admin_status = 2; //XXX start - do we hold a peer for admin stopped state?
    return true;
}

bool
BGPMain::get_peer_negotiated_version(const Iptuple& iptuple,
				     int32_t& neg_version)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    if (peer->state() == STATEESTABLISHED)
	neg_version = 4; /* we only support BGP 4 */
    else
	neg_version = 0; /* XXX the MIB doesn't say what version
			    should be reported when the connection
			    isn't established */
    return true;
}

bool
BGPMain::get_peer_as(const Iptuple& iptuple, uint32_t& peer_as)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    const BGPPeerData* pd = peer->peerdata();

    // XXX is it appropriate to return an extended AS number in this
    // context?
    peer_as = pd->as().as32();

    return true;
}

bool
BGPMain::get_peer_msg_stats(const Iptuple& iptuple,
			    uint32_t& in_updates,
			    uint32_t& out_updates,
			    uint32_t& in_msgs,
			    uint32_t& out_msgs,
			    uint16_t& last_error,
			    uint32_t& in_update_elapsed)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    peer->get_msg_stats(in_updates, out_updates, in_msgs, out_msgs,
			last_error, in_update_elapsed);
    return true;
}

bool
BGPMain::get_peer_established_stats(const Iptuple& iptuple,
				    uint32_t& transitions,
				    uint32_t& established_time)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    transitions = peer->get_established_transitions();
    established_time = peer->get_established_time();
    return true;
}

bool
BGPMain::get_peer_timer_config(const Iptuple& iptuple,
			       uint32_t& retry_interval,
			       uint32_t& hold_time,
			       uint32_t& keep_alive,
			       uint32_t& hold_time_configured,
			       uint32_t& keep_alive_configured,
			       uint32_t& min_as_origination_interval,
			       uint32_t& min_route_adv_interval)
{
    BGPPeer *peer = find_peer(iptuple);

    if (0 == peer) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    const BGPPeerData* pd = peer->peerdata();
    retry_interval = (pd->get_retry_duration() / 1000);
    hold_time = (pd->get_hold_duration() / 1000);
    keep_alive = (pd->get_keepalive_duration() / 1000);
    hold_time_configured = pd->get_configured_hold_time();
    keep_alive_configured = hold_time_configured/3; //XXX
    min_as_origination_interval = 0; //XXX
    min_route_adv_interval = 0; //XXX
    return true;
}


bool
BGPMain::register_ribname(const string& name)
{
    debug_msg("%s\n", name.c_str());

    if (!_rib_ipc_handler->register_ribname(name))
	return false;

    if (!plumbing_unicast()->
	plumbing_ipv4().next_hop_resolver().register_ribname(name))
	return false;

    if (!plumbing_unicast()->
	plumbing_ipv6().next_hop_resolver().register_ribname(name))
	return false;

    return true;
}

int
BGPMain::create_listener(const Iptuple& iptuple)
{
    SocketServer s = SocketServer(iptuple, eventloop());
    s.create_listener();
    s.listen();
    return s.get_sock();
}

LocalData*
BGPMain::get_local_data()
{
    return &_local_data;
}

void
BGPMain::start_server(const Iptuple& iptuple)
{
    debug_msg("starting server on %s\n", iptuple.str().c_str());

    /*
    ** Its possible to be called with the same iptuple multiple
    ** times. Because repeated calls to enable are possible.
    ** Filter out the repeat calls.
    */
    bool match = false;
    list<Server>::iterator i;
    for (i = _serverfds.begin(); i != _serverfds.end(); i++) {
	list<Iptuple>::iterator j;
	for (j = i->_tuples.begin(); j != i->_tuples.end(); j++) {
	    if (*j == iptuple)	// This tuple already in list.
		return;
	    if ((j->get_local_addr() ==
		iptuple.get_local_addr() &&
		j->get_local_port() == iptuple.get_local_port()))
		match = true;
	}
	/*
	** If we are already listening on this address/port pair then
	** add the iptuple to the list and return.
	*/
	if (match) {
	    i->_tuples.push_back(iptuple);
	    return;
	}
    }

    int sfd = create_listener(iptuple);
    if (!eventloop().
	add_selector(sfd,
		     SEL_RD,
		     callback(this, &BGPMain::connect_attempt,
			      iptuple.get_local_addr(),
			      iptuple.get_local_port()))) {
	XLOG_ERROR("Failed to add socket %d to eventloop", sfd);
    }
    _serverfds.push_back(Server(sfd, iptuple));
}

void
BGPMain::stop_server(const Iptuple& iptuple)
{
    debug_msg("stopping server on %s\n", iptuple.str().c_str());

    list<Server>::iterator i;
    for (i = _serverfds.begin(); i != _serverfds.end(); i++) {
	list<Iptuple>::iterator j;
	for (j = i->_tuples.begin(); j != i->_tuples.end(); j++) {
	    if (*j == iptuple) {
		i->_tuples.erase(j);
		if (i->_tuples.empty()) {
		    eventloop().remove_selector(i->_serverfd);
		    ::close(i->_serverfd);
		    _serverfds.erase(i);
		}
		return;
	    }
	}
    }
    XLOG_WARNING("Attempt to remove a listener that doesn't exist: %s",
	       iptuple.str().c_str());
}

void
BGPMain::stop_all_servers()
{
    debug_msg("stop_all_servers\n");

    list<Server>::iterator i;
    for (i = _serverfds.begin(); i != _serverfds.end();) {
	debug_msg("%s\n", i->str().c_str());
	eventloop().remove_selector(i->_serverfd);
	::close(i->_serverfd);
	_serverfds.erase(i++);
    }
}

bool
BGPMain::originate_route(const IPv4Net& nlri, const IPv4& next_hop,
			  const bool& unicast, const bool& multicast,
			  const PolicyTags& policytags)
{
    debug_msg("nlri %s next hop %s unicast %d multicast %d\n",
	      nlri.str().c_str(), next_hop.str().c_str(), unicast, multicast);

    AsPath aspath;

    return _rib_ipc_handler->originate_route(INCOMPLETE, aspath, nlri,
					     next_hop, unicast,
					     multicast, policytags);
}

bool
BGPMain::originate_route(const IPv6Net& nlri, const IPv6& next_hop,
			  const bool& unicast, const bool& multicast,
			  const PolicyTags& policytags)
{
    debug_msg("nlri %s next hop %s unicast %d multicast %d\n",
	      nlri.str().c_str(), next_hop.str().c_str(), unicast, multicast);

    AsPath aspath;

    return _rib_ipc_handler->originate_route(INCOMPLETE, aspath, nlri,
					      next_hop, unicast,
					      multicast, policytags);
}

bool
BGPMain::withdraw_route(const IPv4Net& nlri, const bool& unicast,
			 const bool& multicast) const
{
    debug_msg("nlri %s unicast %d multicast %d\n",
	      nlri.str().c_str(), unicast, multicast);

    return _rib_ipc_handler->withdraw_route(nlri, unicast, multicast);
}

bool
BGPMain::withdraw_route(const IPv6Net& nlri, const bool& unicast,
			 const bool& multicast) const
{
    debug_msg("nlri %s unicast %d multicast %d\n",
	      nlri.str().c_str(), unicast, multicast);

    return _rib_ipc_handler->withdraw_route(nlri, unicast, multicast);
}

template <> 
BGPMain::RoutingTableToken& 
BGPMain::get_token_table<IPv4>()
{
    return _table_ipv4;
}

template <>
BGPMain::RoutingTableToken&
BGPMain::get_token_table<IPv6>()
{
    return _table_ipv6;
}


bool
BGPMain::rib_client_route_info_changed4(const IPv4& addr,
					const uint32_t& prefix_len,
					const IPv4& nexthop,
					const uint32_t& metric)
{
    debug_msg("rib_client_route_info_changed4:"
	      " addr %s prefix_len %u nexthop %s metric %u\n",
	      addr.str().c_str(), XORP_UINT_CAST(prefix_len),
	      nexthop.str().c_str(), XORP_UINT_CAST(metric));

    return plumbing_unicast()->plumbing_ipv4().
	next_hop_resolver().rib_client_route_info_changed(addr, prefix_len,
							  nexthop, metric);
}

bool
BGPMain::rib_client_route_info_changed6(const IPv6& addr,
					const uint32_t& prefix_len,
					const IPv6& nexthop,
					const uint32_t& metric)
{
    debug_msg("rib_client_route_info_changed6:"
	      " addr %s prefix_len %u nexthop %s metric %u\n",
	      addr.str().c_str(), XORP_UINT_CAST(prefix_len),
	      nexthop.str().c_str(), XORP_UINT_CAST(metric));

    return plumbing_unicast()->plumbing_ipv6().
	next_hop_resolver().rib_client_route_info_changed(addr, prefix_len,
							  nexthop, metric);
}

bool
BGPMain::rib_client_route_info_invalid4(const IPv4& addr,
					const uint32_t& prefix_len)
{
    debug_msg("rib_client_route_info_invalid4:"
	      " addr %s prefix_len %u\n", addr.str().c_str(),
	      XORP_UINT_CAST(prefix_len));

    return plumbing_unicast()->plumbing_ipv4().
	next_hop_resolver().rib_client_route_info_invalid(addr, prefix_len);
}

bool
BGPMain::rib_client_route_info_invalid6(const IPv6& addr,
					const uint32_t& prefix_len)
{
    debug_msg("rib_client_route_info_invalid6:"
	      " addr %s prefix_len %u\n", addr.str().c_str(),
	      XORP_UINT_CAST(prefix_len));

    return plumbing_unicast()->plumbing_ipv6().
	next_hop_resolver().rib_client_route_info_invalid(addr, prefix_len);
}

bool
BGPMain::set_parameter(const Iptuple& iptuple , const string& parameter,
		       const bool toggle)
{
    BGPPeer *peer;
    // BGPPeerData *peerdata;

    if ((0 == (peer = find_peer(iptuple)))) {
	XLOG_WARNING("Could not find peer: %s", iptuple.str().c_str());
	return false;
    }

    ParameterNode node;
    if (strcmp(parameter.c_str(),"Refresh_Capability") == 0) {
	/*
	** This is a place holder and example as to how to set
	** parameters/capabilities on a per per basis. Currently Route
	** Refresh isn't supported, but it is a nice example. APG - 2002-10-21
	*/
	XLOG_WARNING("No support for route refresh (yet).");
// 	debug_msg("Setting Refresh capability for peer %s.",
// 		  iptuple.str().c_str());
// 	peerdata = const_cast<BGPPeerData *const>(peer->peerdata());
// 	peerdata->add_sent_parameter( new BGPRefreshCapability() );
    } else if (strcmp(parameter.c_str(),"MultiProtocol.IPv4.Unicast") == 0) {
 	debug_msg("IPv4 Unicast\n");
	node = new BGPMultiProtocolCapability(AFI_IPV4, SAFI_UNICAST);
    } else if (strcmp(parameter.c_str(),"MultiProtocol.IPv4.Multicast") == 0) {
 	debug_msg("IPv4 Multicast\n");
	node = new BGPMultiProtocolCapability(AFI_IPV4, SAFI_MULTICAST);
    } else if (strcmp(parameter.c_str(),"MultiProtocol.IPv6.Unicast") == 0) {
 	debug_msg("IPv6 Unicast\n");
	node = new BGPMultiProtocolCapability(AFI_IPV6, SAFI_UNICAST);
    } else if (strcmp(parameter.c_str(),"MultiProtocol.IPv6.Multicast") == 0) {
 	debug_msg("IPv6 Multicast\n");
	node = new BGPMultiProtocolCapability(AFI_IPV6, SAFI_MULTICAST);
    } else {
	XLOG_WARNING("Unable to set unknown parameter: <%s>.",
		     parameter.c_str());
	return false;
    }
    
    debug_msg("Peer %s. %s\n", iptuple.str().c_str(),toggle ? "true" :"false");

    BGPPeerData *peerdata = const_cast<BGPPeerData *const>(peer->peerdata());
    if (toggle) {
	peerdata->add_sent_parameter(node);
    } else {
	peerdata->remove_sent_parameter(node);
    }
    return true;
}

void
BGPMain::configure_filter(const uint32_t& filter, const string& conf) {
    _policy_filters.configure(filter,conf);
}

void
BGPMain::reset_filter(const uint32_t& filter) {
    _policy_filters.reset(filter);
}

void
BGPMain::push_routes() {
    _plumbing_unicast->push_routes();
    _plumbing_multicast->push_routes();
}

