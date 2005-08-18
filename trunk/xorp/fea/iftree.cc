// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

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

#ident "$XORP: xorp/fea/iftree.cc,v 1.27 2005/03/25 02:53:08 pavlin Exp $"

#include "fea_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/c_format.hh"

#include "iftree.hh"


/* ------------------------------------------------------------------------- */
/* Misc */

static inline const char* true_false(bool b)
{
    return b ? "true" : "false";
}

/* ------------------------------------------------------------------------- */
/* IfTreeItem code */

string
IfTreeItem::str() const
{
    struct {
	State st;
	const char* desc;
    } t[] = { { CREATED,  "CREATED"  },
	      { DELETED,  "DELETED"  },
	      { CHANGED, "CHANGED" }
    };

    string r;
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
	if ((_st & t[i].st) == 0) continue;
	if (r.empty() == false) r += ",";
	r += t[i].desc;
    }
    return r;
}

/* ------------------------------------------------------------------------- */
/* IfTree code */

void
IfTree::clear()
{
    _ifs.clear();
}

bool
IfTree::add_if(const string& ifname)
{
    IfMap::iterator ii = get_if(ifname);
    if (ii != ifs().end()) {
	ii->second.mark(CREATED);
	return true;
    }
    _ifs.insert(IfMap::value_type(ifname, IfTreeInterface(ifname)));
    return true;
}

bool
IfTree::remove_if(const string& ifname)
{
    IfMap::iterator ii = get_if(ifname);
    if (ii == ifs().end())
	return false;

    ii->second.mark(DELETED);
    return true;
}

/**
 * Create a new interface or update its state if it already exists.
 *
 * @param other_iface the interface with the state to copy from.
 *
 * @return true on success, false if an error.
 */
bool
IfTree::update_if(const IfTreeInterface& other_iface)
{
    IfTree::IfMap::iterator ii;
    IfTreeInterface::VifMap::iterator vi;
    IfTreeInterface::VifMap::const_iterator ov;

    //
    // Add the interface if we don't have it already
    //
    ii = get_if(other_iface.ifname());
    if (ii == ifs().end()) {
	add_if(other_iface.ifname());
	ii = get_if(other_iface.ifname());
    }
    IfTreeInterface& this_iface = ii->second;

    //
    // Update the interface state
    //
    if (! this_iface.is_same_state(other_iface))
	this_iface.copy_state(other_iface);

    //
    // Update existing vifs and addresses
    //
    for (vi = this_iface.vifs().begin();
	 vi != this_iface.vifs().end();
	 ++vi) {
	IfTreeVif& this_vif = vi->second;

	ov = other_iface.get_vif(this_vif.vifname());
	if (ov == other_iface.vifs().end()) {
	    this_vif.mark(DELETED);
	    continue;
	}
	const IfTreeVif& other_vif = ov->second;

	if (! this_vif.is_same_state(this_vif))
	    this_vif.copy_state(other_vif);

	IfTreeVif::V4Map::iterator ai4;
	for (ai4 = this_vif.v4addrs().begin();
	     ai4 != this_vif.v4addrs().end();
	     ++ai4) {
	    IfTreeVif::V4Map::const_iterator oa4;
	    oa4 = other_vif.get_addr(ai4->second.addr());
	    if (oa4 == other_vif.v4addrs().end()) {
		ai4->second.mark(DELETED);
		continue;
	    }
	    if (! ai4->second.is_same_state(oa4->second))
		ai4->second.copy_state(oa4->second);
	}

	IfTreeVif::V6Map::iterator ai6;
	for (ai6 = this_vif.v6addrs().begin();
	     ai6 != this_vif.v6addrs().end();
	     ++ai6) {
	    IfTreeVif::V6Map::const_iterator oa6;
	    oa6 = other_vif.get_addr(ai6->second.addr());
	    if (oa6 == other_vif.v6addrs().end()) {
		ai6->second.mark(DELETED);
		continue;
	    }
	    if (! ai6->second.is_same_state(oa6->second))
		ai6->second.copy_state(oa6->second);
	}
    }

    //
    // Add the new vifs and addresses
    //
    for (ov = other_iface.vifs().begin();
	 ov != other_iface.vifs().end();
	 ++ov) {
	const IfTreeVif& other_vif = ov->second;

	if (this_iface.get_vif(other_vif.vifname()) != this_iface.vifs().end())
	    continue;		// The vif was already updated

	// Add the vif
	this_iface.add_vif(other_vif.vifname());
	vi = this_iface.get_vif(other_vif.vifname());
	IfTreeVif& this_vif = vi->second;
	this_vif.copy_state(other_vif);

	// Add the IPv4 addresses
	IfTreeVif::V4Map::const_iterator oa4;
	for (oa4 = other_vif.v4addrs().begin();
	     oa4 != other_vif.v4addrs().end();
	     ++oa4) {
	    IfTreeVif::V4Map::iterator ai4;
	    ai4 = this_vif.get_addr(oa4->second.addr());
	    if (ai4 != this_vif.v4addrs().end())
		continue;	// The address was already updated

	    // Add the address
	    this_vif.add_addr(oa4->second.addr());
	    ai4 = this_vif.get_addr(oa4->second.addr());
	    ai4->second.copy_state(oa4->second);
	}

	// Add the IPv6 addresses
	IfTreeVif::V6Map::const_iterator oa6;
	for (oa6 = other_vif.v6addrs().begin();
	     oa6 != other_vif.v6addrs().end();
	     ++oa6) {
	    IfTreeVif::V6Map::iterator ai6;
	    ai6 = this_vif.get_addr(oa6->second.addr());
	    if (ai6 != this_vif.v6addrs().end())
		continue;	// The address was already updated

	    // Add the address
	    this_vif.add_addr(oa6->second.addr());
	    ai6 = this_vif.get_addr(oa6->second.addr());
	    ai6->second.copy_state(oa6->second);
	}
    }

    return true;
}

void
IfTree::finalize_state()
{
    IfMap::iterator ii = _ifs.begin();
    while (ii != _ifs.end()) {
	//
	// If interface is marked as deleted, delete it.
	//
	if (ii->second.is_marked(DELETED)) {
	    _ifs.erase(ii++);
	    continue;
	}
	//
	// Call finalize_state on interfaces that remain
	//
	ii->second.finalize_state();
	++ii;
    }
    set_state(NO_CHANGE);
}

string
IfTree::str() const
{
    string r;
    for (IfMap::const_iterator ii = ifs().begin(); ii != ifs().end(); ++ii) {
	const IfTreeInterface& fi = ii->second;
	r += fi.str() + string("\n");
	for (IfTreeInterface::VifMap::const_iterator vi = fi.vifs().begin();
	     vi != fi.vifs().end(); ++vi) {
	    const IfTreeVif& fv = vi->second;
	    r += string("  ") + fv.str() + string("\n");
	    for (IfTreeVif::V4Map::const_iterator ai = fv.v4addrs().begin();
		 ai != fv.v4addrs().end(); ++ai) {
		const IfTreeAddr4& a = ai->second;
		r += string("    ") + a.str() + string("\n");
	    }
	    for (IfTreeVif::V6Map::const_iterator ai = fv.v6addrs().begin();
		 ai != fv.v6addrs().end(); ++ai) {
		const IfTreeAddr6& a = ai->second;
		r += string("    ") + a.str() + string("\n");
	    }
	}
    }

    return r;
}

//
// Walk interfaces, vifs, and addresses and align them with the other tree:
//  - If the item in the local tree is "disabled", then the state is not
//    modified. Otherwise, the rules below are applied.
//  - If an item from the local tree is not in the other tree,
//    it is marked as deleted in the local tree.
//    However, if an interface from the local tree is marked as "soft"
//    or "discard_emulated", and is not in the other tree, the interface
//    is not marked as deleted in the local tree.
//  - If an item from the local tree is in the other tree,
//    its state is copied from the other tree to the local tree.
//  - If an item from the other tree is not in the local tree, we do NOT
//    copy it to the local tree.
//
// Return the aligned local tree.
//
IfTree&
IfTree::align_with(const IfTree& o)
{
    IfTree::IfMap::iterator ii;
    for (ii = ifs().begin(); ii != ifs().end(); ++ii) {
	if (! ii->second.enabled())
	    continue;		// XXX: don't do anything to disabled state
	const string& ifname = ii->second.ifname();
	IfTree::IfMap::const_iterator oi = o.get_if(ifname);
	if (oi == o.ifs().end()) {
	    //
	    // Mark local interface for deletion, not present in other,
	    // unless the local interface is marked as "soft" or
	    // "discard_emulated".
	    //
	    if (! (ii->second.is_soft() || ii->second.is_discard_emulated()))
		ii->second.mark(DELETED);
	    continue;
	} else {
	    if (! ii->second.is_same_state(oi->second))
		ii->second.copy_state(oi->second);
	}

	IfTreeInterface::VifMap::iterator vi;
	for (vi = ii->second.vifs().begin();
	     vi != ii->second.vifs().end(); ++vi) {
	    if (! vi->second.enabled())
		continue;	// XXX: don't do anything to disabled state
	    const string& vifname = vi->second.vifname();
	    IfTreeInterface::VifMap::const_iterator ov =
		oi->second.get_vif(vifname);
	    if (ov == oi->second.vifs().end()) {
		vi->second.mark(DELETED);
		continue;
	    } else {
		if (! vi->second.is_same_state(ov->second))
		    vi->second.copy_state(ov->second);
	    }

	    IfTreeVif::V4Map::iterator ai4;
	    for (ai4 = vi->second.v4addrs().begin();
		 ai4 != vi->second.v4addrs().end(); ++ai4) {
		if (! ai4->second.enabled())
		    continue;	// XXX: don't do anything to disabled state
		IfTreeVif::V4Map::const_iterator oa4 =
		    ov->second.get_addr(ai4->second.addr());
		if (oa4 == ov->second.v4addrs().end()) {
		    ai4->second.mark(DELETED);
		} else {
		    if (! ai4->second.is_same_state(oa4->second))
			ai4->second.copy_state(oa4->second);
		}
	    }

	    IfTreeVif::V6Map::iterator ai6;
	    for (ai6 = vi->second.v6addrs().begin();
		 ai6 != vi->second.v6addrs().end(); ++ai6) {
		if (! ai6->second.enabled())
		    continue;	// XXX: don't do anything to disabled state
		IfTreeVif::V6Map::const_iterator oa6 =
		    ov->second.get_addr(ai6->second.addr());
		if (oa6 == ov->second.v6addrs().end()) {
		    ai6->second.mark(DELETED);
		} else {
		    if (! ai6->second.is_same_state(oa6->second))
			ai6->second.copy_state(oa6->second);
		}
	    }
	}
    }

    return *this;
}

/**
 * Prune bogus deleted state.
 * 
 * If an item from the local tree is marked as deleted, but is not
 * in the other tree, then it is removed.
 * 
 * @param old_iftree the old tree with the state that is used as reference.
 * @return the modified configuration tree.
 */
IfTree&
IfTree::prune_bogus_deleted_state(const IfTree& old_iftree)
{
    IfTree::IfMap::iterator ii;
    ii = _ifs.begin();
    while (ii != _ifs.end()) {
	const string& ifname = ii->second.ifname();
	if (! ii->second.is_marked(DELETED)) {
	    ++ii;
	    continue;
	}
	IfTree::IfMap::const_iterator oi;
	oi = old_iftree.get_if(ifname);
	if (oi == old_iftree.ifs().end()) {
	    // Remove this item from the local tree
	    _ifs.erase(ii++);
	    continue;
	}

	IfTreeInterface::VifMap::iterator vi;
	vi = ii->second.vifs().begin();
	while (vi != ii->second.vifs().end()) {
	    const string& vifname = vi->second.vifname();
	    if (! vi->second.is_marked(DELETED)) {
		++vi;
		continue;
	    }
	    IfTreeInterface::VifMap::const_iterator ov;
	    ov = oi->second.get_vif(vifname);
	    if (ov == oi->second.vifs().end()) {
		// Remove this item from the local tree
		ii->second.vifs().erase(vi++);
		continue;
	    }

	    IfTreeVif::V4Map::iterator ai4;
	    ai4 = vi->second.v4addrs().begin();
	    while (ai4 != vi->second.v4addrs().end()) {
		if (! ai4->second.is_marked(DELETED)) {
		    ++ai4;
		    continue;
		}
		IfTreeVif::V4Map::const_iterator oa4;
		oa4 = ov->second.get_addr(ai4->second.addr());
		if (oa4 == ov->second.v4addrs().end()) {
		    // Remove this item from the local tree
		    vi->second.v4addrs().erase(ai4++);
		    continue;
		}
		++ai4;
	    }

	    IfTreeVif::V6Map::iterator ai6;
	    ai6 = vi->second.v6addrs().begin();
	    while (ai6 != vi->second.v6addrs().end()) {
		if (! ai6->second.is_marked(DELETED)) {
		    ++ai6;
		    continue;
		}
		IfTreeVif::V6Map::const_iterator oa6;
		oa6 = ov->second.get_addr(ai6->second.addr());
		if (oa6 == ov->second.v6addrs().end()) {
		    // Remove this item from the local tree
		    vi->second.v6addrs().erase(ai6++);
		    continue;
		}
		++ai6;
	    }
	    ++vi;
	}
	++ii;
    }

    return *this;
}

/* ------------------------------------------------------------------------- */
/* IfTreeInterface code */

IfTreeInterface::IfTreeInterface(const string& ifname)
    : IfTreeItem(), _ifname(ifname), _pif_index(0),
      _enabled(false), _discard(false), _is_discard_emulated(false),
      _mtu(0), _if_flags(0)
{}

bool
IfTreeInterface::add_vif(const string& vifname)
{
    VifMap::iterator vi = get_vif(vifname);
    if (vi != _vifs.end()) {
	vi->second.mark(CREATED);
	return true;
    }
    _vifs.insert(VifMap::value_type(vifname, IfTreeVif(name(), vifname)));
    return true;
}

bool
IfTreeInterface::remove_vif(const string& vifname)
{
    VifMap::iterator vi = get_vif(vifname);
    if (vi == _vifs.end())
	return false;
    vi->second.mark(DELETED);
    return true;
}

void
IfTreeInterface::finalize_state()
{
    VifMap::iterator vi = _vifs.begin();
    while (vi != _vifs.end()) {
	//
	// If interface is marked as deleted, delete it.
	//
	if (vi->second.is_marked(DELETED)) {
	    _vifs.erase(vi++);
	    continue;
	}
	//
	// Call finalize_state on vifs that remain
	//
	vi->second.finalize_state();
	++vi;
    }
    set_state(NO_CHANGE);
}

string
IfTreeInterface::str() const
{
    return c_format("Interface %s { enabled := %s } "
		    "{ mtu := %u } { mac := %s } { flags := %u }",
		    _ifname.c_str(), true_false(_enabled),
		    XORP_UINT_CAST(_mtu),
		    _mac.str().c_str(),
		    XORP_UINT_CAST(_if_flags))
	+ string(" ")
	+ IfTreeItem::str();
}

/* ------------------------------------------------------------------------- */
/* IfTreeVif code */

IfTreeVif::IfTreeVif(const string& ifname, const string& vifname)
    : IfTreeItem(), _ifname(ifname), _vifname(vifname),
      _pif_index(0), _enabled(false),
      _broadcast(false), _loopback(false), _point_to_point(false),
      _multicast(false)
{}

bool
IfTreeVif::add_addr(const IPv4& v4addr)
{
    V4Map::iterator ai = get_addr(v4addr);
    if (ai != v4addrs().end()) {
	ai->second.mark(CREATED);
	return true;
    }
    _v4addrs.insert(V4Map::value_type(v4addr, IfTreeAddr4(v4addr)));
    return true;
}

bool
IfTreeVif::remove_addr(const IPv4& v4addr)
{
    V4Map::iterator ai = get_addr(v4addr);
    if (ai == v4addrs().end())
	return false;
    ai->second.mark(DELETED);
    return true;
}

bool
IfTreeVif::add_addr(const IPv6& v6addr)
{
    V6Map::iterator ai = get_addr(v6addr);
    if (ai != v6addrs().end()) {
	ai->second.mark(CREATED);
	return true;
    }
    _v6addrs.insert(V6Map::value_type(v6addr, IfTreeAddr6(v6addr)));
    return true;
}

bool
IfTreeVif::remove_addr(const IPv6& v6addr)
{
    V6Map::iterator ai = get_addr(v6addr);
    if (ai == v6addrs().end())
	return false;
    ai->second.mark(DELETED);
    return true;
}

void
IfTreeVif::finalize_state()
{
    for (V4Map::iterator ai = _v4addrs.begin(); ai != _v4addrs.end(); ) {
	//
	// If address is marked as deleted, delete it.
	//
	if (ai->second.is_marked(DELETED)) {
	    _v4addrs.erase(ai++);
	    continue;
	}
	//
	// Call finalize_state on addresses that remain
	//
	ai->second.finalize_state();
	++ai;
    }

    for (V6Map::iterator ai = _v6addrs.begin(); ai != _v6addrs.end(); ) {
	//
	// If address is marked as deleted, delete it.
	//
	if (ai->second.is_marked(DELETED)) {
	    _v6addrs.erase(ai++);
	    continue;
	}
	//
	// Call finalize_state on interfaces that remain
	//
	ai->second.finalize_state();
	++ai;
    }
    set_state(NO_CHANGE);
}

string
IfTreeVif::str() const
{
    return c_format("VIF %s { enabled := %s } { broadcast := %s } "
		    "{ loopback := %s } { point_to_point := %s } "
		    "{ multicast := %s } ",
		    _vifname.c_str(), true_false(_enabled),
		    true_false(_broadcast), true_false(_loopback),
		    true_false(_point_to_point), true_false(_multicast))
	+ string(" ") + IfTreeItem::str();
}

/* ------------------------------------------------------------------------- */
/* IfTreeAddr4 code */

bool
IfTreeAddr4::set_prefix_len(uint32_t prefix_len)
{
    if (prefix_len > IPv4::addr_bitlen())
	return false;

    _prefix_len = prefix_len;
    mark(CHANGED);
    return true;
}

void
IfTreeAddr4::set_bcast(const IPv4& baddr)
{
    _oaddr = baddr;
    mark(CHANGED);
}

IPv4
IfTreeAddr4::bcast() const
{
    if (broadcast())
	return _oaddr;
    return IPv4::ZERO();
}

void
IfTreeAddr4::set_endpoint(const IPv4& oaddr)
{
    _oaddr = oaddr;
    mark(CHANGED);
}

IPv4
IfTreeAddr4::endpoint() const
{
    if (point_to_point())
	return _oaddr;
    return IPv4::ZERO();
}

void
IfTreeAddr4::finalize_state()
{
    set_state(NO_CHANGE);
}

string
IfTreeAddr4::str() const
{
    string r = c_format("V4Addr %s { enabled := %s } { broadcast := %s } "
			"{ loopback := %s } { point_to_point := %s } "
			"{ multicast := %s } "
			"{ prefix_len := %u }",
			_addr.str().c_str(), true_false(_enabled),
			true_false(_broadcast), true_false(_loopback),
			true_false(_point_to_point), true_false(_multicast),
			XORP_UINT_CAST(_prefix_len));
    if (_point_to_point)
	r += c_format(" { endpoint := %s }", _oaddr.str().c_str());
    if (_broadcast)
	r += c_format(" { broadcast := %s }", _oaddr.str().c_str());
    r += string(" ") + IfTreeItem::str();
    return r;
}

/* ------------------------------------------------------------------------- */
/* IfTreeAddr6 code */

bool
IfTreeAddr6::set_prefix_len(uint32_t prefix_len)
{
    if (prefix_len > IPv6::addr_bitlen())
	return false;

    _prefix_len = prefix_len;
    mark(CHANGED);
    return true;
}

void
IfTreeAddr6::set_endpoint(const IPv6& oaddr)
{
    _oaddr = oaddr;
    mark(CHANGED);
}

IPv6
IfTreeAddr6::endpoint() const
{
    if (point_to_point())
	return _oaddr;
    return IPv6::ZERO();
}

void
IfTreeAddr6::finalize_state()
{
    set_state(NO_CHANGE);
}

string
IfTreeAddr6::str() const
{
    string r = c_format("V6Addr %s { enabled := %s } "
			"{ loopback := %s } { point_to_point := %s } "
			"{ multicast := %s } "
			"{ prefix_len := %u }",
			_addr.str().c_str(), true_false(_enabled),
			true_false(_loopback),
			true_false(_point_to_point), true_false(_multicast),
			XORP_UINT_CAST(_prefix_len));
    if (_point_to_point)
	r += c_format(" { endpoint := %s }", _oaddr.str().c_str());
    r += string(" ") + IfTreeItem::str();
    return r;
}
