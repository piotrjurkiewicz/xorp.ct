/*
 * Copyright (c) 2001-2004 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/rip_xif.hh,v 1.3 2004/05/31 04:06:39 hodson Exp $
 */

#ifndef __XRL_INTERFACES_RIP_XIF_HH__
#define __XRL_INTERFACES_RIP_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifRip"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlRipV0p1Client {
public:
    XrlRipV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlRipV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddRipAddressCB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an address to run RIP process on. The addition of address is not
     *  instantaneous, RIP has to instantiate state in the FEA to send and
     *  receive packets. Once instantiated the address must be explicitly
     *  enabled with set_rip_address_enabled.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be added.
     */
    bool send_add_rip_address(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const AddRipAddressCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr RemoveRipAddressCB;
    /**
     *  Send Xrl intended to:
     *
     *  Remove an address RIP process is running on.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be removed.
     */
    bool send_remove_rip_address(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const RemoveRipAddressCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetRipAddressEnabledCB;

    bool send_set_rip_address_enabled(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	enabled,
	const SetRipAddressEnabledCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr RipAddressEnabledCB;

    bool send_rip_address_enabled(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const RipAddressEnabledCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetCostCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set cost metric associated with address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_cost(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	cost,
	const SetCostCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr CostCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get cost metric associated with address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_cost(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const CostCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetHorizonCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set horizon type applied to routes advertised from address.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param horizon name of horizon type. Permitted values: "none",
     *  "poison-reverse" "split-horizon-poison-reverse"
     */
    bool send_set_horizon(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const string&	horizon,
	const SetHorizonCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr HorizonCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get horizon type applied to routes advertised from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_horizon(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const HorizonCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetPassiveCB;
    /**
     *  Send Xrl intended to:
     *
     *  Make RIP passive (receive only) on interface/vif/address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_passive(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	passive,
	const SetPassiveCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr PassiveCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get value indicating whether RIP is passive (receive only) on
     *  interface/vif/address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_passive(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const PassiveCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetAcceptNonRipRequestsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Accept and respond to non-RIP requests.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_accept_non_rip_requests(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	accept,
	const SetAcceptNonRipRequestsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr AcceptNonRipRequestsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get value indicating whether non-RIP requests are accepted and
     *  responded to on interface/vif/address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_accept_non_rip_requests(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const AcceptNonRipRequestsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetAcceptDefaultRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Accept default route from peers.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_accept_default_route(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	accept,
	const SetAcceptDefaultRouteCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr AcceptDefaultRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Accessor for whether default route is accepted from peers.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_accept_default_route(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const AcceptDefaultRouteCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetAdvertiseDefaultRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Advertise default route (if present).
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_advertise_default_route(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	advertise,
	const SetAdvertiseDefaultRouteCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr AdvertiseDefaultRouteCB;
    /**
     *  Send Xrl intended to:
     *
     *  Accessor for whether default route is advertised.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_advertise_default_route(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const AdvertiseDefaultRouteCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetRouteExpirySecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set period that routes associated with reception address will expire in
     *  the absence of updates.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_route_expiry_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetRouteExpirySecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr RouteExpirySecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get period that routes associated with reception address will expire in
     *  the absence of updates.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_route_expiry_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const RouteExpirySecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetRouteDeletionSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set period that routes associated with reception address will be
     *  deleted after they've expired.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_route_deletion_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetRouteDeletionSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr RouteDeletionSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get period that routes associated with reception address will be
     *  deleted after they've expired.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_route_deletion_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const RouteDeletionSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetTableRequestSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_table_request_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetTableRequestSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr TableRequestSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_table_request_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const TableRequestSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetUnsolicitedResponseMinSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set minimum period between the unsolicited sending of the routing table
     *  from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_unsolicited_response_min_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetUnsolicitedResponseMinSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr UnsolicitedResponseMinSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get minimum period between the unsolicited sending of the routing table
     *  from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_unsolicited_response_min_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const UnsolicitedResponseMinSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetUnsolicitedResponseMaxSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set maximum period between the unsolicited sending of the routing table
     *  from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_unsolicited_response_max_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetUnsolicitedResponseMaxSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr UnsolicitedResponseMaxSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get maximum period between the unsolicited sending of the routing table
     *  from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_unsolicited_response_max_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const UnsolicitedResponseMaxSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetTriggeredUpdateMinSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set minimum period between sending triggered updates from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_triggered_update_min_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetTriggeredUpdateMinSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr TriggeredUpdateMinSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get minimum period between sending triggered updates from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_triggered_update_min_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const TriggeredUpdateMinSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetTriggeredUpdateMaxSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set maximum period between sending triggered updates from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_triggered_update_max_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs,
	const SetTriggeredUpdateMaxSecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr TriggeredUpdateMaxSecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get maximum period between sending triggered updates from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_triggered_update_max_seconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const TriggeredUpdateMaxSecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetInterpacketDelayMillisecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set the inter-packet delay between the output of packets from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_interpacket_delay_milliseconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_msecs,
	const SetInterpacketDelayMillisecondsCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr InterpacketDelayMillisecondsCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the inter-packet delay between the output of packets from address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_interpacket_delay_milliseconds(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const InterpacketDelayMillisecondsCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetAuthenticationCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set authentication scheme.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_authentication(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const string&	type,
	const string&	password,
	const SetAuthenticationCB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const string*, const string*>::RefPtr AuthenticationCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get authentication scheme.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_authentication(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const AuthenticationCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr RipAddressStatusCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get a textual description of the status of address RIP is running upon.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname the interface that owns vif that has the address.
     *
     *  @param vifname virtual interface owns the address.
     *
     *  @param addr the address to query.
     */
    bool send_rip_address_status(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const RipAddressStatusCB&	cb
    );

    typedef XorpCallback4<void, const XrlError&, const XrlAtomList*, const XrlAtomList*, const XrlAtomList*>::RefPtr GetAllAddressesCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get addresses running RIP.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_all_addresses(
	const char*	target_name,
	const GetAllAddressesCB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const XrlAtomList*, const XrlAtomList*>::RefPtr GetCountersCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get counters associated with interface / vif /address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_counters(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const GetCountersCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const XrlAtomList*>::RefPtr GetPeersCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the list of peers associated with interface / vif / address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_peers(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const GetPeersCB&	cb
    );

    typedef XorpCallback5<void, const XrlError&, const XrlAtomList*, const XrlAtomList*, const XrlAtomList*, const XrlAtomList*>::RefPtr GetAllPeersCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get list of all peers known to RIP. There is a 1-to-1 correspondence
     *  between the items in the lists of peers, ifnames, vifnames, addrs.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_all_peers(
	const char*	target_name,
	const GetAllPeersCB&	cb
    );

    typedef XorpCallback4<void, const XrlError&, const XrlAtomList*, const XrlAtomList*, const uint32_t*>::RefPtr GetPeerCountersCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get counters associated with peer of interface / vif /address.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_peer_counters(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const IPv4&	peer,
	const GetPeerCountersCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr ImportProtocolRoutesCB;
    /**
     *  Send Xrl intended to:
     *
     *  Configure protocol route import.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param protocol_name name of protocol to import routes from.
     *
     *  @param cost RIP cost metric to assign to protocol routes.
     *
     *  @param tag RIP tag to associate with protocol routes.
     */
    bool send_import_protocol_routes(
	const char*	target_name,
	const string&	protocol_name,
	const uint32_t&	cost,
	const uint32_t&	tag,
	const ImportProtocolRoutesCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr NoImportProtocolRoutesCB;
    /**
     *  Send Xrl intended to:
     *
     *  Remove protocol route import.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param protocol_name name of protocol to stop import of routes from.
     */
    bool send_no_import_protocol_routes(
	const char*	target_name,
	const string&	protocol_name,
	const NoImportProtocolRoutesCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_add_rip_address(
	const XrlError&	e,
	XrlArgs*	a,
	AddRipAddressCB		cb
    );

    void unmarshall_remove_rip_address(
	const XrlError&	e,
	XrlArgs*	a,
	RemoveRipAddressCB		cb
    );

    void unmarshall_set_rip_address_enabled(
	const XrlError&	e,
	XrlArgs*	a,
	SetRipAddressEnabledCB		cb
    );

    void unmarshall_rip_address_enabled(
	const XrlError&	e,
	XrlArgs*	a,
	RipAddressEnabledCB		cb
    );

    void unmarshall_set_cost(
	const XrlError&	e,
	XrlArgs*	a,
	SetCostCB		cb
    );

    void unmarshall_cost(
	const XrlError&	e,
	XrlArgs*	a,
	CostCB		cb
    );

    void unmarshall_set_horizon(
	const XrlError&	e,
	XrlArgs*	a,
	SetHorizonCB		cb
    );

    void unmarshall_horizon(
	const XrlError&	e,
	XrlArgs*	a,
	HorizonCB		cb
    );

    void unmarshall_set_passive(
	const XrlError&	e,
	XrlArgs*	a,
	SetPassiveCB		cb
    );

    void unmarshall_passive(
	const XrlError&	e,
	XrlArgs*	a,
	PassiveCB		cb
    );

    void unmarshall_set_accept_non_rip_requests(
	const XrlError&	e,
	XrlArgs*	a,
	SetAcceptNonRipRequestsCB		cb
    );

    void unmarshall_accept_non_rip_requests(
	const XrlError&	e,
	XrlArgs*	a,
	AcceptNonRipRequestsCB		cb
    );

    void unmarshall_set_accept_default_route(
	const XrlError&	e,
	XrlArgs*	a,
	SetAcceptDefaultRouteCB		cb
    );

    void unmarshall_accept_default_route(
	const XrlError&	e,
	XrlArgs*	a,
	AcceptDefaultRouteCB		cb
    );

    void unmarshall_set_advertise_default_route(
	const XrlError&	e,
	XrlArgs*	a,
	SetAdvertiseDefaultRouteCB		cb
    );

    void unmarshall_advertise_default_route(
	const XrlError&	e,
	XrlArgs*	a,
	AdvertiseDefaultRouteCB		cb
    );

    void unmarshall_set_route_expiry_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetRouteExpirySecondsCB		cb
    );

    void unmarshall_route_expiry_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	RouteExpirySecondsCB		cb
    );

    void unmarshall_set_route_deletion_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetRouteDeletionSecondsCB		cb
    );

    void unmarshall_route_deletion_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	RouteDeletionSecondsCB		cb
    );

    void unmarshall_set_table_request_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetTableRequestSecondsCB		cb
    );

    void unmarshall_table_request_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	TableRequestSecondsCB		cb
    );

    void unmarshall_set_unsolicited_response_min_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnsolicitedResponseMinSecondsCB		cb
    );

    void unmarshall_unsolicited_response_min_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	UnsolicitedResponseMinSecondsCB		cb
    );

    void unmarshall_set_unsolicited_response_max_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnsolicitedResponseMaxSecondsCB		cb
    );

    void unmarshall_unsolicited_response_max_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	UnsolicitedResponseMaxSecondsCB		cb
    );

    void unmarshall_set_triggered_update_min_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetTriggeredUpdateMinSecondsCB		cb
    );

    void unmarshall_triggered_update_min_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	TriggeredUpdateMinSecondsCB		cb
    );

    void unmarshall_set_triggered_update_max_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetTriggeredUpdateMaxSecondsCB		cb
    );

    void unmarshall_triggered_update_max_seconds(
	const XrlError&	e,
	XrlArgs*	a,
	TriggeredUpdateMaxSecondsCB		cb
    );

    void unmarshall_set_interpacket_delay_milliseconds(
	const XrlError&	e,
	XrlArgs*	a,
	SetInterpacketDelayMillisecondsCB		cb
    );

    void unmarshall_interpacket_delay_milliseconds(
	const XrlError&	e,
	XrlArgs*	a,
	InterpacketDelayMillisecondsCB		cb
    );

    void unmarshall_set_authentication(
	const XrlError&	e,
	XrlArgs*	a,
	SetAuthenticationCB		cb
    );

    void unmarshall_authentication(
	const XrlError&	e,
	XrlArgs*	a,
	AuthenticationCB		cb
    );

    void unmarshall_rip_address_status(
	const XrlError&	e,
	XrlArgs*	a,
	RipAddressStatusCB		cb
    );

    void unmarshall_get_all_addresses(
	const XrlError&	e,
	XrlArgs*	a,
	GetAllAddressesCB		cb
    );

    void unmarshall_get_counters(
	const XrlError&	e,
	XrlArgs*	a,
	GetCountersCB		cb
    );

    void unmarshall_get_peers(
	const XrlError&	e,
	XrlArgs*	a,
	GetPeersCB		cb
    );

    void unmarshall_get_all_peers(
	const XrlError&	e,
	XrlArgs*	a,
	GetAllPeersCB		cb
    );

    void unmarshall_get_peer_counters(
	const XrlError&	e,
	XrlArgs*	a,
	GetPeerCountersCB		cb
    );

    void unmarshall_import_protocol_routes(
	const XrlError&	e,
	XrlArgs*	a,
	ImportProtocolRoutesCB		cb
    );

    void unmarshall_no_import_protocol_routes(
	const XrlError&	e,
	XrlArgs*	a,
	NoImportProtocolRoutesCB		cb
    );

};

#endif /* __XRL_INTERFACES_RIP_XIF_HH__ */
