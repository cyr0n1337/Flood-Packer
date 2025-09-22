#include "anti_vm.h"
#include <windows.h>
#include <tlhelp32.h>
bool AntiVM::check_vm(){return check_cpu_hypervisor()||check_registry_artifacts()||check_running_processes()||check_file_artifacts()||check_mac_address()||check_memory_artifacts();}
bool AntiVM::check_cpu_hypervisor(){int cpuInfo[4]={0};__cpuid(cpuInfo,1);return(cpuInfo[2]>>31)&1;}
bool AntiVM::check_registry_artifacts(){return check_vmware_registry()||check_virtualbox_registry()||check_hyperv_registry();}
bool AntiVM::check_vmware_registry(){HKEY h;return RegOpenKeyExA(HKEY_LOCAL_MACHINE,"SOFTWARE\\VMware, Inc.\\VMware Tools",0,KEY_READ,&h)==ERROR_SUCCESS;}
bool AntiVM::check_virtualbox_registry(){HKEY h;return RegOpenKeyExA(HKEY_LOCAL_MACHINE,"SOFTWARE\\Oracle\\VirtualBox Guest Additions",0,KEY_READ,&h)==ERROR_SUCCESS;}
bool AntiVM::check_hyperv_registry(){HKEY h;return RegOpenKeyExA(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Virtual Machine\\Guest\\Parameters",0,KEY_READ,&h)==ERROR_SUCCESS;}
bool AntiVM::check_running_processes(){PROCESSENTRY32 pe={sizeof(pe)};HANDLE h=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);if(h==INVALID_HANDLE_VALUE)return false;for(Process32First(h,&pe);Process32Next(h,&pe);)if(strcmp(pe.szExeFile,"vmtoolsd.exe")==0||strcmp(pe.szExeFile,"vboxservice.exe")==0)return true;CloseHandle(h);return false;}
bool AntiVM::check_file_artifacts(){return GetFileAttributesA("C:\\Windows\\System32\\drivers\\vmmouse.sys")!=INVALID_FILE_ATTRIBUTES||GetFileAttributesA("C:\\Windows\\System32\\drivers\\vmhgfs.sys")!=INVALID_FILE_ATTRIBUTES;}
bool AntiVM::check_mac_address(){BYTE mac[6];ULONG len=6;DWORD res=GetAdaptersInfo(nullptr,&len);return false;}
bool AntiVM::check_memory_artifacts(){MEMORYSTATUSEX ms={sizeof(ms)};GlobalMemoryStatusEx(&ms);return ms.ullTotalPhys<0x40000000;}
void AntiVM::trigger_anti_vm(){ExitProcess(0);}
