/*
 * Copyright (c) 2001-2004 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP$
 */

#ifndef __XRL_INTERFACES_FIREWALL_XIF_HH__
#define __XRL_INTERFACES_FIREWALL_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifFirewall"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlFirewallV0p1Client {
public:
    XrlFirewallV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlFirewallV0p1Client() {}

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr GetFwEnabledCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get global IP filter enable status.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_fw_enabled(
	const char*	target_name,
	const GetFwEnabledCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetFwEnabledCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set global IP filter enable status.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param enabled Enable or disable IP filtering.
     */
    bool send_set_fw_enabled(
	const char*	target_name,
	const bool&	enabled,
	const SetFwEnabledCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr GetFwDefaultDropCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get global IP filter default-to-drop status.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_fw_default_drop(
	const char*	target_name,
	const GetFwDefaultDropCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetFwDefaultDropCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set global IP filter default-to-drop status.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_set_fw_default_drop(
	const char*	target_name,
	const bool&	drop,
	const SetFwDefaultDropCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr GetFwProviderCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the underlying IP filter provider type in use.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_fw_provider(
	const char*	target_name,
	const GetFwProviderCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetFwProviderCB;
    /**
     *  Send Xrl intended to:
     *
     *  Set the underlying IP filter provider type in use.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param provider Name of an IP firewall provider to use on systems which
     *  have multiple IP filtering providers.
     */
    bool send_set_fw_provider(
	const char*	target_name,
	const string&	provider,
	const SetFwProviderCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr GetFwVersionCB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the underlying IP filter provider version in use.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_fw_version(
	const char*	target_name,
	const GetFwVersionCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr GetNumXorpRules4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the number of IPv4 firewall rules installed by XORP.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_num_xorp_rules4(
	const char*	target_name,
	const GetNumXorpRules4CB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr GetNumProviderRules4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the number of IPv4 firewall rules actually visible to the
     *  underlying provider in the FEA.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_num_provider_rules4(
	const char*	target_name,
	const GetNumProviderRules4CB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr GetNumXorpRules6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the number of IPv6 firewall rules installed by XORP.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_num_xorp_rules6(
	const char*	target_name,
	const GetNumXorpRules6CB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const uint32_t*>::RefPtr GetNumProviderRules6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the number of IPv6 firewall rules actually visible to the
     *  underlying provider in the FEA.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_num_provider_rules6(
	const char*	target_name,
	const GetNumProviderRules6CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddFilter4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an IPv4 family filter rule.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname Name of the interface where this filter is to be applied.
     *
     *  @param vifname Name of the vif where this filter is to be applied.
     *
     *  @param src Source IPv4 address with network prefix.
     *
     *  @param dst Destination IPv4 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param action Action to take when this filter is matched.
     */
    bool send_add_filter4(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4Net&	src,
	const IPv4Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const string&	action,
	const AddFilter4CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddFilter6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an IPv6 family filter rule.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname Name of the interface where this filter is to be applied.
     *
     *  @param vifname Name of the vif where this filter is to be applied.
     *
     *  @param src Source IPv6 address with network prefix.
     *
     *  @param dst Destination IPv6 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param action Action to take when this filter is matched.
     */
    bool send_add_filter6(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv6Net&	src,
	const IPv6Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const string&	action,
	const AddFilter6CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteFilter4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete an IPv4 family filter rule.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname Name of the interface where this filter is to be deleted.
     *
     *  @param vifname Name of the vif where this filter is to be deleted.
     *
     *  @param src Source IPv4 address with network prefix.
     *
     *  @param dst Destination IPv4 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     */
    bool send_delete_filter4(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv4Net&	src,
	const IPv4Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const DeleteFilter4CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteFilter6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete an IPv6 family filter rule.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param ifname Name of the interface where this filter is to be deleted.
     *
     *  @param vifname Name of the vif where this filter is to be deleted.
     *
     *  @param src Source IPv6 address with network prefix.
     *
     *  @param dst Destination IPv6 address with network prefix.
     *
     *  @param proto IP protocol number for match (0-255, 255 is wildcard).
     *
     *  @param sport Source TCP/UDP port (0-65535, 0 is wildcard).
     *
     *  @param dport Destination TCP/UDP port (0-65535, 0 is wildcard).
     */
    bool send_delete_filter6(
	const char*	target_name,
	const string&	ifname,
	const string&	vifname,
	const IPv6Net&	src,
	const IPv6Net&	dst,
	const uint32_t&	proto,
	const uint32_t&	sport,
	const uint32_t&	dport,
	const DeleteFilter6CB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const uint32_t*, const bool*>::RefPtr GetFilterListStart4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the first IPv4 family filter rule configured in the system.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_filter_list_start4(
	const char*	target_name,
	const GetFilterListStart4CB&	cb
    );

    typedef XorpCallback10<void, const XrlError&, const bool*, const string*, const string*, const IPv4Net*, const IPv4Net*, const uint32_t*, const uint32_t*, const uint32_t*, const string*>::RefPtr GetFilterListNext4CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the next IPv4 family filter rule configured in the system.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param token token from prior call to get_filter_list_start4.
     */
    bool send_get_filter_list_next4(
	const char*	target_name,
	const uint32_t&	token,
	const GetFilterListNext4CB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const uint32_t*, const bool*>::RefPtr GetFilterListStart6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the first IPv6 family filter rule configured in the system.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_get_filter_list_start6(
	const char*	target_name,
	const GetFilterListStart6CB&	cb
    );

    typedef XorpCallback10<void, const XrlError&, const bool*, const string*, const string*, const IPv6Net*, const IPv6Net*, const uint32_t*, const uint32_t*, const uint32_t*, const string*>::RefPtr GetFilterListNext6CB;
    /**
     *  Send Xrl intended to:
     *
     *  Get the next IPv6 family filter rule configured in the system.
     *
     *  @param tgt_name Xrl Target name
     *
     *  @param token token from prior call to get_filter_list_start6.
     */
    bool send_get_filter_list_next6(
	const char*	target_name,
	const uint32_t&	token,
	const GetFilterListNext6CB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_get_fw_enabled(
	const XrlError&	e,
	XrlArgs*	a,
	GetFwEnabledCB		cb
    );

    void unmarshall_set_fw_enabled(
	const XrlError&	e,
	XrlArgs*	a,
	SetFwEnabledCB		cb
    );

    void unmarshall_get_fw_default_drop(
	const XrlError&	e,
	XrlArgs*	a,
	GetFwDefaultDropCB		cb
    );

    void unmarshall_set_fw_default_drop(
	const XrlError&	e,
	XrlArgs*	a,
	SetFwDefaultDropCB		cb
    );

    void unmarshall_get_fw_provider(
	const XrlError&	e,
	XrlArgs*	a,
	GetFwProviderCB		cb
    );

    void unmarshall_set_fw_provider(
	const XrlError&	e,
	XrlArgs*	a,
	SetFwProviderCB		cb
    );

    void unmarshall_get_fw_version(
	const XrlError&	e,
	XrlArgs*	a,
	GetFwVersionCB		cb
    );

    void unmarshall_get_num_xorp_rules4(
	const XrlError&	e,
	XrlArgs*	a,
	GetNumXorpRules4CB		cb
    );

    void unmarshall_get_num_provider_rules4(
	const XrlError&	e,
	XrlArgs*	a,
	GetNumProviderRules4CB		cb
    );

    void unmarshall_get_num_xorp_rules6(
	const XrlError&	e,
	XrlArgs*	a,
	GetNumXorpRules6CB		cb
    );

    void unmarshall_get_num_provider_rules6(
	const XrlError&	e,
	XrlArgs*	a,
	GetNumProviderRules6CB		cb
    );

    void unmarshall_add_filter4(
	const XrlError&	e,
	XrlArgs*	a,
	AddFilter4CB		cb
    );

    void unmarshall_add_filter6(
	const XrlError&	e,
	XrlArgs*	a,
	AddFilter6CB		cb
    );

    void unmarshall_delete_filter4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteFilter4CB		cb
    );

    void unmarshall_delete_filter6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteFilter6CB		cb
    );

    void unmarshall_get_filter_list_start4(
	const XrlError&	e,
	XrlArgs*	a,
	GetFilterListStart4CB		cb
    );

    void unmarshall_get_filter_list_next4(
	const XrlError&	e,
	XrlArgs*	a,
	GetFilterListNext4CB		cb
    );

    void unmarshall_get_filter_list_start6(
	const XrlError&	e,
	XrlArgs*	a,
	GetFilterListStart6CB		cb
    );

    void unmarshall_get_filter_list_next6(
	const XrlError&	e,
	XrlArgs*	a,
	GetFilterListNext6CB		cb
    );

};

#endif /* __XRL_INTERFACES_FIREWALL_XIF_HH__ */
