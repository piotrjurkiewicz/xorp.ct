/*
 * Copyright (c) 2001-2007 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/redist4_xif.hh,v 1.13 2006/03/30 02:21:15 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_REDIST4_XIF_HH__
#define __XRL_INTERFACES_REDIST4_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifRedist4"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlRedist4V0p1Client {
public:
    XrlRedist4V0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlRedist4V0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Add/delete a routing entry.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param dst destination network.
     *
     *  @param nexthop nexthop router address.
     *
     *  @param ifname interface name associated with nexthop.
     *
     *  @param vifname virtual interface name with nexthop.
     *
     *  @param metric origin routing protocol metric for route.
     *
     *  @param admin_distance administrative distance of origin routing
     *  protocol.
     *
     *  @param cookie value set by the requestor to identify redistribution
     *  source. Typical value is the originating protocol name.
     *
     *  @param protocol_origin the name of the protocol that originated this
     *  routing entry.
     */
    bool send_add_route(
	const char*	dst_xrl_target_name,
	const IPv4Net&	dst,
	const IPv4&	nexthop,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	metric,
	const uint32_t&	admin_distance,
	const string&	cookie,
	const string&	protocol_origin,
	const AddRouteCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteRouteCB;

    bool send_delete_route(
	const char*	dst_xrl_target_name,
	const IPv4Net&	dst,
	const IPv4&	nexthop,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	metric,
	const uint32_t&	admin_distance,
	const string&	cookie,
	const string&	protocol_origin,
	const DeleteRouteCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr StartingRouteDumpCB;
    /**
     *  Send Xrl intended to:
     *
     *  When route redistribution begins, the receiver is sent the existing
     *  list of routes. This message marks the beginning of the routes being
     *  sent.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param cookie value set by the requestor to identify redistribution
     *  source. Typical value is the originating protocol name.
     */
    bool send_starting_route_dump(
	const char*	dst_xrl_target_name,
	const string&	cookie,
	const StartingRouteDumpCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr FinishingRouteDumpCB;
    /**
     *  Send Xrl intended to:
     *
     *  When route redistribution begins, the receiver is sent the existing
     *  list of routes. This message marks the end of the existing routes being
     *  sent.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param cookie value set by the requestor to identify redistribution
     *  source. Typical value is the originating protocol name.
     */
    bool send_finishing_route_dump(
	const char*	dst_xrl_target_name,
	const string&	cookie,
	const FinishingRouteDumpCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_add_route(
	const XrlError&	e,
	XrlArgs*	a,
	AddRouteCB		cb
    );

    void unmarshall_delete_route(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteRouteCB		cb
    );

    void unmarshall_starting_route_dump(
	const XrlError&	e,
	XrlArgs*	a,
	StartingRouteDumpCB		cb
    );

    void unmarshall_finishing_route_dump(
	const XrlError&	e,
	XrlArgs*	a,
	FinishingRouteDumpCB		cb
    );

};

#endif /* __XRL_INTERFACES_REDIST4_XIF_HH__ */
