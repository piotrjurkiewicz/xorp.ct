/*
 * Copyright (c) 2001-2007 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/fti_xif.cc,v 1.17 2006/10/17 22:26:10 pavlin Exp $"

#include "fti_xif.hh"

bool
XrlFtiV0p2Client::send_lookup_route_by_dest4(
	const char*	dst_xrl_target_name,
	const IPv4&	dst,
	const LookupRouteByDest4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/lookup_route_by_dest4");
    x.args().add("dst", dst);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_lookup_route_by_dest4, cb));
}


/* Unmarshall lookup_route_by_dest4 */
void
XrlFtiV0p2Client::unmarshall_lookup_route_by_dest4(
	const XrlError&	e,
	XrlArgs*	a,
	LookupRouteByDest4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0, 0, 0, 0, 0, 0);
	return;
    } else if (a && a->size() != 7) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(7));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0, 0);
	return;
    }
    IPv4Net netmask;
    IPv4 nexthop;
    string ifname;
    string vifname;
    uint32_t metric;
    uint32_t admin_distance;
    string protocol_origin;
    try {
	a->get("netmask", netmask);
	a->get("nexthop", nexthop);
	a->get("ifname", ifname);
	a->get("vifname", vifname);
	a->get("metric", metric);
	a->get("admin_distance", admin_distance);
	a->get("protocol_origin", protocol_origin);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0, 0);
	return;
    }
    cb->dispatch(e, &netmask, &nexthop, &ifname, &vifname, &metric, &admin_distance, &protocol_origin);
}

bool
XrlFtiV0p2Client::send_lookup_route_by_dest6(
	const char*	dst_xrl_target_name,
	const IPv6&	dst,
	const LookupRouteByDest6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/lookup_route_by_dest6");
    x.args().add("dst", dst);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_lookup_route_by_dest6, cb));
}


/* Unmarshall lookup_route_by_dest6 */
void
XrlFtiV0p2Client::unmarshall_lookup_route_by_dest6(
	const XrlError&	e,
	XrlArgs*	a,
	LookupRouteByDest6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0, 0, 0, 0, 0, 0);
	return;
    } else if (a && a->size() != 7) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(7));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0, 0);
	return;
    }
    IPv6Net netmask;
    IPv6 nexthop;
    string ifname;
    string vifname;
    uint32_t metric;
    uint32_t admin_distance;
    string protocol_origin;
    try {
	a->get("netmask", netmask);
	a->get("nexthop", nexthop);
	a->get("ifname", ifname);
	a->get("vifname", vifname);
	a->get("metric", metric);
	a->get("admin_distance", admin_distance);
	a->get("protocol_origin", protocol_origin);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0, 0);
	return;
    }
    cb->dispatch(e, &netmask, &nexthop, &ifname, &vifname, &metric, &admin_distance, &protocol_origin);
}

bool
XrlFtiV0p2Client::send_lookup_route_by_network4(
	const char*	dst_xrl_target_name,
	const IPv4Net&	dst,
	const LookupRouteByNetwork4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/lookup_route_by_network4");
    x.args().add("dst", dst);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_lookup_route_by_network4, cb));
}


/* Unmarshall lookup_route_by_network4 */
void
XrlFtiV0p2Client::unmarshall_lookup_route_by_network4(
	const XrlError&	e,
	XrlArgs*	a,
	LookupRouteByNetwork4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0, 0, 0, 0, 0);
	return;
    } else if (a && a->size() != 6) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(6));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0);
	return;
    }
    IPv4 nexthop;
    string ifname;
    string vifname;
    uint32_t metric;
    uint32_t admin_distance;
    string protocol_origin;
    try {
	a->get("nexthop", nexthop);
	a->get("ifname", ifname);
	a->get("vifname", vifname);
	a->get("metric", metric);
	a->get("admin_distance", admin_distance);
	a->get("protocol_origin", protocol_origin);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0);
	return;
    }
    cb->dispatch(e, &nexthop, &ifname, &vifname, &metric, &admin_distance, &protocol_origin);
}

bool
XrlFtiV0p2Client::send_lookup_route_by_network6(
	const char*	dst_xrl_target_name,
	const IPv6Net&	dst,
	const LookupRouteByNetwork6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/lookup_route_by_network6");
    x.args().add("dst", dst);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_lookup_route_by_network6, cb));
}


/* Unmarshall lookup_route_by_network6 */
void
XrlFtiV0p2Client::unmarshall_lookup_route_by_network6(
	const XrlError&	e,
	XrlArgs*	a,
	LookupRouteByNetwork6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0, 0, 0, 0, 0);
	return;
    } else if (a && a->size() != 6) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(6));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0);
	return;
    }
    IPv6 nexthop;
    string ifname;
    string vifname;
    uint32_t metric;
    uint32_t admin_distance;
    string protocol_origin;
    try {
	a->get("nexthop", nexthop);
	a->get("ifname", ifname);
	a->get("vifname", vifname);
	a->get("metric", metric);
	a->get("admin_distance", admin_distance);
	a->get("protocol_origin", protocol_origin);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0, 0, 0, 0, 0);
	return;
    }
    cb->dispatch(e, &nexthop, &ifname, &vifname, &metric, &admin_distance, &protocol_origin);
}

bool
XrlFtiV0p2Client::send_have_ipv4(
	const char*	dst_xrl_target_name,
	const HaveIpv4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/have_ipv4");
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_have_ipv4, cb));
}


/* Unmarshall have_ipv4 */
void
XrlFtiV0p2Client::unmarshall_have_ipv4(
	const XrlError&	e,
	XrlArgs*	a,
	HaveIpv4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(1));
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    bool result;
    try {
	a->get("result", result);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &result);
}

bool
XrlFtiV0p2Client::send_have_ipv6(
	const char*	dst_xrl_target_name,
	const HaveIpv6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/have_ipv6");
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_have_ipv6, cb));
}


/* Unmarshall have_ipv6 */
void
XrlFtiV0p2Client::unmarshall_have_ipv6(
	const XrlError&	e,
	XrlArgs*	a,
	HaveIpv6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(1));
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    bool result;
    try {
	a->get("result", result);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &result);
}

bool
XrlFtiV0p2Client::send_get_unicast_forwarding_enabled4(
	const char*	dst_xrl_target_name,
	const GetUnicastForwardingEnabled4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/get_unicast_forwarding_enabled4");
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_get_unicast_forwarding_enabled4, cb));
}


/* Unmarshall get_unicast_forwarding_enabled4 */
void
XrlFtiV0p2Client::unmarshall_get_unicast_forwarding_enabled4(
	const XrlError&	e,
	XrlArgs*	a,
	GetUnicastForwardingEnabled4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(1));
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    bool enabled;
    try {
	a->get("enabled", enabled);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &enabled);
}

bool
XrlFtiV0p2Client::send_get_unicast_forwarding_enabled6(
	const char*	dst_xrl_target_name,
	const GetUnicastForwardingEnabled6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/get_unicast_forwarding_enabled6");
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_get_unicast_forwarding_enabled6, cb));
}


/* Unmarshall get_unicast_forwarding_enabled6 */
void
XrlFtiV0p2Client::unmarshall_get_unicast_forwarding_enabled6(
	const XrlError&	e,
	XrlArgs*	a,
	GetUnicastForwardingEnabled6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(1));
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    bool enabled;
    try {
	a->get("enabled", enabled);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &enabled);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_enabled4(
	const char*	dst_xrl_target_name,
	const bool&	enabled,
	const SetUnicastForwardingEnabled4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_enabled4");
    x.args().add("enabled", enabled);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_enabled4, cb));
}


/* Unmarshall set_unicast_forwarding_enabled4 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_enabled4(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEnabled4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_enabled6(
	const char*	dst_xrl_target_name,
	const bool&	enabled,
	const SetUnicastForwardingEnabled6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_enabled6");
    x.args().add("enabled", enabled);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_enabled6, cb));
}


/* Unmarshall set_unicast_forwarding_enabled6 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_enabled6(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEnabled6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_entries_retain_on_startup4(
	const char*	dst_xrl_target_name,
	const bool&	retain,
	const SetUnicastForwardingEntriesRetainOnStartup4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_entries_retain_on_startup4");
    x.args().add("retain", retain);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_startup4, cb));
}


/* Unmarshall set_unicast_forwarding_entries_retain_on_startup4 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_startup4(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEntriesRetainOnStartup4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_entries_retain_on_shutdown4(
	const char*	dst_xrl_target_name,
	const bool&	retain,
	const SetUnicastForwardingEntriesRetainOnShutdown4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_entries_retain_on_shutdown4");
    x.args().add("retain", retain);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_shutdown4, cb));
}


/* Unmarshall set_unicast_forwarding_entries_retain_on_shutdown4 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_shutdown4(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEntriesRetainOnShutdown4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_entries_retain_on_startup6(
	const char*	dst_xrl_target_name,
	const bool&	retain,
	const SetUnicastForwardingEntriesRetainOnStartup6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_entries_retain_on_startup6");
    x.args().add("retain", retain);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_startup6, cb));
}


/* Unmarshall set_unicast_forwarding_entries_retain_on_startup6 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_startup6(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEntriesRetainOnStartup6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFtiV0p2Client::send_set_unicast_forwarding_entries_retain_on_shutdown6(
	const char*	dst_xrl_target_name,
	const bool&	retain,
	const SetUnicastForwardingEntriesRetainOnShutdown6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "fti/0.2/set_unicast_forwarding_entries_retain_on_shutdown6");
    x.args().add("retain", retain);
    return _sender->send(x, callback(this, &XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_shutdown6, cb));
}


/* Unmarshall set_unicast_forwarding_entries_retain_on_shutdown6 */
void
XrlFtiV0p2Client::unmarshall_set_unicast_forwarding_entries_retain_on_shutdown6(
	const XrlError&	e,
	XrlArgs*	a,
	SetUnicastForwardingEntriesRetainOnShutdown6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
