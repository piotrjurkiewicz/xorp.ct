// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2004 International Computer Science Institute
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

#ident "$XORP: xorp/fea/fticonfig_entry_get_dummy.cc,v 1.4 2004/06/02 22:52:36 pavlin Exp $"


#include "fea_module.h"
#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"

#include "libxorp/ipvxnet.hh"

#include "fticonfig.hh"
#include "fticonfig_entry_get.hh"


//
// Get single-entry information from the unicast forwarding table.
//
// The mechanism to obtain the information is dummy (for testing purpose).
//


FtiConfigEntryGetDummy::FtiConfigEntryGetDummy(FtiConfig& ftic)
    : FtiConfigEntryGet(ftic)
{
#if 0	// XXX: by default Dummy is never registering by itself
    register_ftic();
#endif
}

FtiConfigEntryGetDummy::~FtiConfigEntryGetDummy()
{
    stop();
}

int
FtiConfigEntryGetDummy::start()
{
    _is_running = true;

    return (XORP_OK);
}
    
int
FtiConfigEntryGetDummy::stop()
{
    if (! _is_running)
	return (XORP_OK);

    _is_running = false;

    return (XORP_OK);
}

/**
 * Lookup a route.
 *
 * @param dst host address to resolve.
 * @param fte return-by-reference forwarding table entry.
 *
 * @return true on success, otherwise false.
 */
bool
FtiConfigEntryGetDummy::lookup_route4(const IPv4& dst, Fte4& fte)
{
    Trie4::iterator ti = ftic().trie4().find(dst);
    if (ti != ftic().trie4().end()) {
	fte = ti.payload();
	return true;
    }
    
    return false;
}

/**
 * Lookup entry.
 *
 * @param dst network address to resolve.
 * @param fte return-by-reference forwarding table entry.
 *
 * @return true on success, otherwise false.
 */
bool
FtiConfigEntryGetDummy::lookup_entry4(const IPv4Net& dst, Fte4& fte)
{
    Trie4::iterator ti = ftic().trie4().find(dst);
    if (ti != ftic().trie4().end()) {
	fte = ti.payload();
	return true;
    }
    
    return false;
}

/**
 * Lookup a route.
 *
 * @param dst host address to resolve.
 * @param fte return-by-reference forwarding table entry.
 *
 * @return true on success, otherwise false.
 */
bool
FtiConfigEntryGetDummy::lookup_route6(const IPv6& dst, Fte6& fte)
{
    Trie6::iterator ti = ftic().trie6().find(dst);
    if (ti != ftic().trie6().end()) {
	fte = ti.payload();
	return true;
    }
    
    return false;
}

/**
 * Lookup entry.
 *
 * @param dst network address to resolve.
 * @param fte return-by-reference forwarding table entry.
 *
 * @return true on success, otherwise false.
 */
bool
FtiConfigEntryGetDummy::lookup_entry6(const IPv6Net& dst, Fte6& fte)
{ 
    Trie6::iterator ti = ftic().trie6().find(dst);
    if (ti != ftic().trie6().end()) {
	fte = ti.payload();
	return true;
    }
    
    return false;
}
