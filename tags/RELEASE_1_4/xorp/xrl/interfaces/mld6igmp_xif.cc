/*
 * Copyright (c) 2001-2007 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/mld6igmp_xif.cc,v 1.21 2006/03/26 22:39:24 pavlin Exp $"

#include "mld6igmp_xif.hh"

bool
XrlMld6igmpV0p1Client::send_enable_vif(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const bool&	enable,
	const EnableVifCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/enable_vif");
    x.args().add("vif_name", vif_name);
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_enable_vif, cb));
}


/* Unmarshall enable_vif */
void
XrlMld6igmpV0p1Client::unmarshall_enable_vif(
	const XrlError&	e,
	XrlArgs*	a,
	EnableVifCB		cb
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
XrlMld6igmpV0p1Client::send_start_vif(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const StartVifCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/start_vif");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_start_vif, cb));
}


/* Unmarshall start_vif */
void
XrlMld6igmpV0p1Client::unmarshall_start_vif(
	const XrlError&	e,
	XrlArgs*	a,
	StartVifCB		cb
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
XrlMld6igmpV0p1Client::send_stop_vif(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const StopVifCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/stop_vif");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_stop_vif, cb));
}


/* Unmarshall stop_vif */
void
XrlMld6igmpV0p1Client::unmarshall_stop_vif(
	const XrlError&	e,
	XrlArgs*	a,
	StopVifCB		cb
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
XrlMld6igmpV0p1Client::send_enable_all_vifs(
	const char*	dst_xrl_target_name,
	const bool&	enable,
	const EnableAllVifsCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/enable_all_vifs");
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_enable_all_vifs, cb));
}


/* Unmarshall enable_all_vifs */
void
XrlMld6igmpV0p1Client::unmarshall_enable_all_vifs(
	const XrlError&	e,
	XrlArgs*	a,
	EnableAllVifsCB		cb
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
XrlMld6igmpV0p1Client::send_start_all_vifs(
	const char*	dst_xrl_target_name,
	const StartAllVifsCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/start_all_vifs");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_start_all_vifs, cb));
}


/* Unmarshall start_all_vifs */
void
XrlMld6igmpV0p1Client::unmarshall_start_all_vifs(
	const XrlError&	e,
	XrlArgs*	a,
	StartAllVifsCB		cb
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
XrlMld6igmpV0p1Client::send_stop_all_vifs(
	const char*	dst_xrl_target_name,
	const StopAllVifsCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/stop_all_vifs");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_stop_all_vifs, cb));
}


/* Unmarshall stop_all_vifs */
void
XrlMld6igmpV0p1Client::unmarshall_stop_all_vifs(
	const XrlError&	e,
	XrlArgs*	a,
	StopAllVifsCB		cb
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
XrlMld6igmpV0p1Client::send_enable_mld6igmp(
	const char*	dst_xrl_target_name,
	const bool&	enable,
	const EnableMld6IgmpCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/enable_mld6igmp");
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_enable_mld6igmp, cb));
}


/* Unmarshall enable_mld6igmp */
void
XrlMld6igmpV0p1Client::unmarshall_enable_mld6igmp(
	const XrlError&	e,
	XrlArgs*	a,
	EnableMld6IgmpCB		cb
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
XrlMld6igmpV0p1Client::send_start_mld6igmp(
	const char*	dst_xrl_target_name,
	const StartMld6IgmpCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/start_mld6igmp");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_start_mld6igmp, cb));
}


/* Unmarshall start_mld6igmp */
void
XrlMld6igmpV0p1Client::unmarshall_start_mld6igmp(
	const XrlError&	e,
	XrlArgs*	a,
	StartMld6IgmpCB		cb
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
XrlMld6igmpV0p1Client::send_stop_mld6igmp(
	const char*	dst_xrl_target_name,
	const StopMld6IgmpCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/stop_mld6igmp");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_stop_mld6igmp, cb));
}


/* Unmarshall stop_mld6igmp */
void
XrlMld6igmpV0p1Client::unmarshall_stop_mld6igmp(
	const XrlError&	e,
	XrlArgs*	a,
	StopMld6IgmpCB		cb
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
XrlMld6igmpV0p1Client::send_enable_cli(
	const char*	dst_xrl_target_name,
	const bool&	enable,
	const EnableCliCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/enable_cli");
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_enable_cli, cb));
}


/* Unmarshall enable_cli */
void
XrlMld6igmpV0p1Client::unmarshall_enable_cli(
	const XrlError&	e,
	XrlArgs*	a,
	EnableCliCB		cb
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
XrlMld6igmpV0p1Client::send_start_cli(
	const char*	dst_xrl_target_name,
	const StartCliCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/start_cli");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_start_cli, cb));
}


/* Unmarshall start_cli */
void
XrlMld6igmpV0p1Client::unmarshall_start_cli(
	const XrlError&	e,
	XrlArgs*	a,
	StartCliCB		cb
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
XrlMld6igmpV0p1Client::send_stop_cli(
	const char*	dst_xrl_target_name,
	const StopCliCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/stop_cli");
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_stop_cli, cb));
}


/* Unmarshall stop_cli */
void
XrlMld6igmpV0p1Client::unmarshall_stop_cli(
	const XrlError&	e,
	XrlArgs*	a,
	StopCliCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_proto_version(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifProtoVersionCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_proto_version");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_proto_version, cb));
}


/* Unmarshall get_vif_proto_version */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_proto_version(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifProtoVersionCB		cb
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
    uint32_t proto_version;
    try {
	a->get("proto_version", proto_version);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &proto_version);
}

bool
XrlMld6igmpV0p1Client::send_set_vif_proto_version(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const uint32_t&	proto_version,
	const SetVifProtoVersionCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_proto_version");
    x.args().add("vif_name", vif_name);
    x.args().add("proto_version", proto_version);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_proto_version, cb));
}


/* Unmarshall set_vif_proto_version */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_proto_version(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifProtoVersionCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_proto_version(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifProtoVersionCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_proto_version");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_proto_version, cb));
}


/* Unmarshall reset_vif_proto_version */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_proto_version(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifProtoVersionCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_ip_router_alert_option_check(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifIpRouterAlertOptionCheckCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_ip_router_alert_option_check");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_ip_router_alert_option_check, cb));
}


/* Unmarshall get_vif_ip_router_alert_option_check */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_ip_router_alert_option_check(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifIpRouterAlertOptionCheckCB		cb
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
XrlMld6igmpV0p1Client::send_set_vif_ip_router_alert_option_check(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const bool&	enable,
	const SetVifIpRouterAlertOptionCheckCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_ip_router_alert_option_check");
    x.args().add("vif_name", vif_name);
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_ip_router_alert_option_check, cb));
}


/* Unmarshall set_vif_ip_router_alert_option_check */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_ip_router_alert_option_check(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifIpRouterAlertOptionCheckCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_ip_router_alert_option_check(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifIpRouterAlertOptionCheckCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_ip_router_alert_option_check");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_ip_router_alert_option_check, cb));
}


/* Unmarshall reset_vif_ip_router_alert_option_check */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_ip_router_alert_option_check(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifIpRouterAlertOptionCheckCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_query_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifQueryIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_query_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_query_interval, cb));
}


/* Unmarshall get_vif_query_interval */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_query_interval(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifQueryIntervalCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0);
	return;
    } else if (a && a->size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(2));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    uint32_t interval_sec;
    uint32_t interval_usec;
    try {
	a->get("interval_sec", interval_sec);
	a->get("interval_usec", interval_usec);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    cb->dispatch(e, &interval_sec, &interval_usec);
}

bool
XrlMld6igmpV0p1Client::send_set_vif_query_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const uint32_t&	interval_sec,
	const uint32_t&	interval_usec,
	const SetVifQueryIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_query_interval");
    x.args().add("vif_name", vif_name);
    x.args().add("interval_sec", interval_sec);
    x.args().add("interval_usec", interval_usec);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_query_interval, cb));
}


/* Unmarshall set_vif_query_interval */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_query_interval(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifQueryIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_query_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifQueryIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_query_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_interval, cb));
}


/* Unmarshall reset_vif_query_interval */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_interval(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifQueryIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_query_last_member_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifQueryLastMemberIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_query_last_member_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_query_last_member_interval, cb));
}


/* Unmarshall get_vif_query_last_member_interval */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_query_last_member_interval(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifQueryLastMemberIntervalCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0);
	return;
    } else if (a && a->size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(2));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    uint32_t interval_sec;
    uint32_t interval_usec;
    try {
	a->get("interval_sec", interval_sec);
	a->get("interval_usec", interval_usec);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    cb->dispatch(e, &interval_sec, &interval_usec);
}

bool
XrlMld6igmpV0p1Client::send_set_vif_query_last_member_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const uint32_t&	interval_sec,
	const uint32_t&	interval_usec,
	const SetVifQueryLastMemberIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_query_last_member_interval");
    x.args().add("vif_name", vif_name);
    x.args().add("interval_sec", interval_sec);
    x.args().add("interval_usec", interval_usec);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_query_last_member_interval, cb));
}


/* Unmarshall set_vif_query_last_member_interval */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_query_last_member_interval(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifQueryLastMemberIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_query_last_member_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifQueryLastMemberIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_query_last_member_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_last_member_interval, cb));
}


/* Unmarshall reset_vif_query_last_member_interval */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_last_member_interval(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifQueryLastMemberIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_query_response_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifQueryResponseIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_query_response_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_query_response_interval, cb));
}


/* Unmarshall get_vif_query_response_interval */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_query_response_interval(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifQueryResponseIntervalCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0, 0);
	return;
    } else if (a && a->size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(2));
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    uint32_t interval_sec;
    uint32_t interval_usec;
    try {
	a->get("interval_sec", interval_sec);
	a->get("interval_usec", interval_usec);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0, 0);
	return;
    }
    cb->dispatch(e, &interval_sec, &interval_usec);
}

bool
XrlMld6igmpV0p1Client::send_set_vif_query_response_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const uint32_t&	interval_sec,
	const uint32_t&	interval_usec,
	const SetVifQueryResponseIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_query_response_interval");
    x.args().add("vif_name", vif_name);
    x.args().add("interval_sec", interval_sec);
    x.args().add("interval_usec", interval_usec);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_query_response_interval, cb));
}


/* Unmarshall set_vif_query_response_interval */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_query_response_interval(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifQueryResponseIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_query_response_interval(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifQueryResponseIntervalCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_query_response_interval");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_response_interval, cb));
}


/* Unmarshall reset_vif_query_response_interval */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_query_response_interval(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifQueryResponseIntervalCB		cb
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
XrlMld6igmpV0p1Client::send_get_vif_robust_count(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const GetVifRobustCountCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/get_vif_robust_count");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_get_vif_robust_count, cb));
}


/* Unmarshall get_vif_robust_count */
void
XrlMld6igmpV0p1Client::unmarshall_get_vif_robust_count(
	const XrlError&	e,
	XrlArgs*	a,
	GetVifRobustCountCB		cb
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
    uint32_t robust_count;
    try {
	a->get("robust_count", robust_count);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &robust_count);
}

bool
XrlMld6igmpV0p1Client::send_set_vif_robust_count(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const uint32_t&	robust_count,
	const SetVifRobustCountCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/set_vif_robust_count");
    x.args().add("vif_name", vif_name);
    x.args().add("robust_count", robust_count);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_set_vif_robust_count, cb));
}


/* Unmarshall set_vif_robust_count */
void
XrlMld6igmpV0p1Client::unmarshall_set_vif_robust_count(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifRobustCountCB		cb
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
XrlMld6igmpV0p1Client::send_reset_vif_robust_count(
	const char*	dst_xrl_target_name,
	const string&	vif_name,
	const ResetVifRobustCountCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/reset_vif_robust_count");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_reset_vif_robust_count, cb));
}


/* Unmarshall reset_vif_robust_count */
void
XrlMld6igmpV0p1Client::unmarshall_reset_vif_robust_count(
	const XrlError&	e,
	XrlArgs*	a,
	ResetVifRobustCountCB		cb
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
XrlMld6igmpV0p1Client::send_log_trace_all(
	const char*	dst_xrl_target_name,
	const bool&	enable,
	const LogTraceAllCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/log_trace_all");
    x.args().add("enable", enable);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_log_trace_all, cb));
}


/* Unmarshall log_trace_all */
void
XrlMld6igmpV0p1Client::unmarshall_log_trace_all(
	const XrlError&	e,
	XrlArgs*	a,
	LogTraceAllCB		cb
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
XrlMld6igmpV0p1Client::send_add_protocol4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const AddProtocol4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/add_protocol4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_add_protocol4, cb));
}


/* Unmarshall add_protocol4 */
void
XrlMld6igmpV0p1Client::unmarshall_add_protocol4(
	const XrlError&	e,
	XrlArgs*	a,
	AddProtocol4CB		cb
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
XrlMld6igmpV0p1Client::send_add_protocol6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const AddProtocol6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/add_protocol6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_add_protocol6, cb));
}


/* Unmarshall add_protocol6 */
void
XrlMld6igmpV0p1Client::unmarshall_add_protocol6(
	const XrlError&	e,
	XrlArgs*	a,
	AddProtocol6CB		cb
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
XrlMld6igmpV0p1Client::send_delete_protocol4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const DeleteProtocol4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/delete_protocol4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_delete_protocol4, cb));
}


/* Unmarshall delete_protocol4 */
void
XrlMld6igmpV0p1Client::unmarshall_delete_protocol4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteProtocol4CB		cb
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
XrlMld6igmpV0p1Client::send_delete_protocol6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const DeleteProtocol6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp/0.1/delete_protocol6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    return _sender->send(x, callback(this, &XrlMld6igmpV0p1Client::unmarshall_delete_protocol6, cb));
}


/* Unmarshall delete_protocol6 */
void
XrlMld6igmpV0p1Client::unmarshall_delete_protocol6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteProtocol6CB		cb
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
