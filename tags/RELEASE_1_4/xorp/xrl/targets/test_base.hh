/*
 * Copyright (c) 2001-2007 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/test_base.hh,v 1.18 2006/03/27 00:21:58 pavlin Exp $
 */


#ifndef __XRL_TARGETS_TEST_BASE_HH__
#define __XRL_TARGETS_TEST_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlTestTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlTestTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlTestTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlTestTargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    inline const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    inline const char* version() const { return "test/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Print "hello world".
     */
    virtual XrlCmdError test_1_0_print_hello_world() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Print "hello world" and a user supplied greeting.
     *
     *  @param msg greeting to be printed.
     */
    virtual XrlCmdError test_1_0_print_hello_world_and_message(
	// Input values,
	const string&	msg) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Count number of greetings available.
     */
    virtual XrlCmdError test_1_0_get_greeting_count(
	// Output values,
	int32_t&	num_msgs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get greeting.
     *
     *  @param greeting_num index of greeting.
     *
     *  @param greeting text of greeting.
     */
    virtual XrlCmdError test_1_0_get_greeting(
	// Input values,
	const int32_t&	greeting_num,
	// Output values,
	string&	greeting) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Something that always fails.
     */
    virtual XrlCmdError test_1_0_shoot_foot() = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_1_0_print_hello_world(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_1_0_print_hello_world_and_message(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_1_0_get_greeting_count(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_1_0_get_greeting(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_1_0_shoot_foot(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_TEST_BASE_HH__
