/*
 * Copyright (c) 2001-2004 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/finder_client_xif.hh,v 1.11 2004/05/24 17:35:35 hodson Exp $
 */

#ifndef __XRL_INTERFACES_FINDER_CLIENT_XIF_HH__
#define __XRL_INTERFACES_FINDER_CLIENT_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifFinderClient"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlFinderClientV0p2Client {
public:
    XrlFinderClientV0p2Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlFinderClientV0p2Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr HelloCB;
    /**
     *  Send Xrl intended to:
     *
     *  No op method used by finder to poll for liveness.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_hello(
	const char*	target_name,
	const HelloCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr RemoveXrlFromCacheCB;
    /**
     *  Send Xrl intended to:
     *
     *  Remove Xrl from cache. The client should remove currently cached value
     *  for Xrl from it's cached. On the next invocation of Xrl, the client
     *  will need to consult the Finder for updated information, though
     *  implementations may consult the Finder for updated information before.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_remove_xrl_from_cache(
	const char*	target_name,
	const string&	xrl,
	const RemoveXrlFromCacheCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr RemoveXrlsForTargetFromCacheCB;
    /**
     *  Send Xrl intended to:
     *
     *  Remove all Xrls relating to target from cache.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_remove_xrls_for_target_from_cache(
	const char*	target_name,
	const string&	target_name,
	const RemoveXrlsForTargetFromCacheCB&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const uint32_t*, const string*>::RefPtr DispatchTunneledXrlCB;
    /**
     *  Send Xrl intended to:
     *
     *  Execute tunneled Xrl. Permits finder to call methods on clients through
     *  FinderClient.
     *
     *  @param tgt_name Xrl Target name
     */
    bool send_dispatch_tunneled_xrl(
	const char*	target_name,
	const string&	xrl,
	const DispatchTunneledXrlCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_hello(
	const XrlError&	e,
	XrlArgs*	a,
	HelloCB		cb
    );

    void unmarshall_remove_xrl_from_cache(
	const XrlError&	e,
	XrlArgs*	a,
	RemoveXrlFromCacheCB		cb
    );

    void unmarshall_remove_xrls_for_target_from_cache(
	const XrlError&	e,
	XrlArgs*	a,
	RemoveXrlsForTargetFromCacheCB		cb
    );

    void unmarshall_dispatch_tunneled_xrl(
	const XrlError&	e,
	XrlArgs*	a,
	DispatchTunneledXrlCB		cb
    );

};

#endif /* __XRL_INTERFACES_FINDER_CLIENT_XIF_HH__ */
