#ifndef INTEGRITY_H
#define INTEGRITY_H
#include <vector>
#include <cstdint>
#include <functional>
#include <windows.h>
class IntegrityChecker{
public:
struct CodeRegion{uint8_t* address;size_t size;uint32_t expected_checksum;uint32_t current_checksum;bool critical;std::function<uint32_t(uint8_t*,size_t)> checksum_func;};
IntegrityChecker();
~IntegrityChecker();
void add_region(uint8_t* address,size_t size,bool critical=false,std::function<uint32_t(uint8_t*,size_t)> checksum_func=nullptr);
bool verify_all_regions();
bool verify_region(size_t index);
void repair_region(size_t index);
void self_repair();
static uint32_t crc32_checksum(uint8_t* data,size_t size);
static uint32_t murmur3_checksum(uint8_t* data,size_t size);
static uint32_t sha1_short_checksum(uint8_t* data,size_t size);
void start_monitoring(uint32_t interval_ms=1000);
void stop_monitoring();
private:
std::vector<CodeRegion> regions;
bool monitoring;
HANDLE monitor_thread;
static DWORD WINAPI monitor_thread_func(LPVOID param);
void monitor_regions();
};
#endif
