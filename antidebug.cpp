#include "anti_debug.h"
#include <windows.h>
#include <iostream>
#include <cstring>

typedef NTSTATUS(NTAPI* PNtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
#define ProcessDebugPort 7
#define ProcessDebugObjectHandle 30
#define ProcessDebugFlags 31

bool AntiDebug::check_debugger(){return check_being_traced()||check_debug_registers()||check_ntqueryinformation()||check_closehandle_exception()||check_interrupt_0x2d()||check_security_cookie();}
bool AntiDebug::check_timing(){LARGE_INTEGER freq,start,end;QueryPerformanceFrequency(&freq);QueryPerformanceCounter(&start);Sleep(10);QueryPerformanceCounter(&end);return((end.QuadPart-start.QuadPart)*1000/freq.QuadPart)<8;}
bool AntiDebug::check_breakpoints(void* addr,size_t len){for(size_t i=0;i<len;i++)if(((BYTE*)addr)[i]==0xCC)return true;return false;}
bool AntiDebug::check_debug_registers(){return false;}
bool AntiDebug::check_being_traced(){return IsDebuggerPresent()!=0;}
bool AntiDebug::trigger_anti_debug(){ExitProcess(0);return false;}
bool AntiDebug::check_ntqueryinformation(){HMODULE h=GetModuleHandleA("ntdll.dll");if(!h)return false;auto f=(PNtQueryInformationProcess)GetProcAddress(h,"NtQueryInformationProcess");if(!f)return false;DWORD d=0;NTSTATUS s=f(GetCurrentProcess(),(PROCESSINFOCLASS)ProcessDebugPort,&d,sizeof(d),nullptr);if(NT_SUCCESS(s)&&d!=0)return true;HANDLE hObj=nullptr;s=f(GetCurrentProcess(),(PROCESSINFOCLASS)ProcessDebugObjectHandle,&hObj,sizeof(hObj),nullptr);if(NT_SUCCESS(s)&&hObj!=nullptr)return true;DWORD df=0;s=f(GetCurrentProcess(),(PROCESSINFOCLASS)ProcessDebugFlags,&df,sizeof(df),nullptr);if(NT_SUCCESS(s)&&df==0)return true;return false;}
bool AntiDebug::check_closehandle_exception(){__try{CloseHandle((HANDLE)0x12345678);}__except(EXCEPTION_EXECUTE_HANDLER){return false;}return true;}
bool AntiDebug::check_interrupt_0x2d(){__try{__asm{int 0x2d}}__except(EXCEPTION_EXECUTE_HANDLER){return false;}return true;}
bool AntiDebug::check_security_cookie(){return false;}
void AntiDebug::erase_debug_headers(){}
void AntiDebug::manipulate_debug_registers(){}
