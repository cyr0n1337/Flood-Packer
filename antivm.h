#ifndef ANTIVM_H
#define ANTIVM_H
#include <windows.h>
class AntiVM{
public:
static bool check_vm();
static bool check_cpu_hypervisor();
static bool check_registry_artifacts();
static bool check_running_processes();
static bool check_file_artifacts();
static bool check_mac_address();
static bool check_memory_artifacts();
static void trigger_anti_vm();
private:
static bool check_vmware_registry();
static bool check_virtualbox_registry();
static bool check_hyperv_registry();
};
#endif
