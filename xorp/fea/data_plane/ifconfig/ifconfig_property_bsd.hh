// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2007-2011 XORP, Inc and Others
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License, Version 2, June
// 1991 as published by the Free Software Foundation. Redistribution
// and/or modification of this program under the terms of any other
// version of the GNU General Public License is not permitted.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. For more details,
// see the GNU General Public License, Version 2, a copy of which can be
// found in the XORP LICENSE.gpl file.
// 
// XORP Inc, 2953 Bunker Hill Lane, Suite 204, Santa Clara, CA 95054, USA;
// http://xorp.net

// $XORP: xorp/fea/data_plane/ifconfig/ifconfig_property_bsd.hh,v 1.5 2008/10/02 21:57:06 bms Exp $

#ifndef __FEA_DATA_PLANE_IFCONFIG_IFCONFIG_PROPERTY_BSD_HH__
#define __FEA_DATA_PLANE_IFCONFIG_IFCONFIG_PROPERTY_BSD_HH__

#if	defined(HOST_OS_BSDI)			\
	|| defined(HOST_OS_DRAGONFLYBSD)	\
	|| defined(HOST_OS_FREEBSD)		\
	|| defined(HOST_OS_MACOSX)		\
	|| defined(HOST_OS_NETBSD)		\
	|| defined(HOST_OS_OPENBSD)


#include "fea/ifconfig_property.hh"


class IfConfigPropertyBsd : public IfConfigProperty {
public:
    /**
     * Constructor.
     *
     * @param fea_data_plane_manager the corresponding data plane manager
     * (@ref FeaDataPlaneManager).
     */
    IfConfigPropertyBsd(FeaDataPlaneManager& fea_data_plane_manager);

    /**
     * Virtual destructor.
     */
    virtual ~IfConfigPropertyBsd();
    
private:
    /**
     * Test whether the underlying system supports IPv4.
     * 
     * @return true if the underlying system supports IPv4, otherwise false.
     */
    virtual bool test_have_ipv4() const;

    /**
     * Test whether the underlying system supports IPv6.
     * 
     * @return true if the underlying system supports IPv6, otherwise false.
     */
    virtual bool test_have_ipv6() const;
};

#endif
#endif // __FEA_DATA_PLANE_IFCONFIG_IFCONFIG_PROPERTY_BSD_HH__
