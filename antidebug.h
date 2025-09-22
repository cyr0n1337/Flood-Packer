#ifndef ANTIDEBUG_H
#define ANTIDEBUG_H
#include <windows.h>
class AntiDebug{
public:
static bool check_debugger();
static bool check_timing();
static bool check_breakpoints(void* addr,size_t len);
static bool check_debug_registers();
static bool check_being_traced();
static void trigger_anti_debug();
static bool check_ntqueryinformation();
static bool check_closehandle_exception();
static bool check_interrupt_0x2d();
static bool check_security_cookie();
static void erase_debug_headers();
static void manipulate_debug_registers();
};
#endif
