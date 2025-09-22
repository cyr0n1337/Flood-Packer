
#ifndef VM_H
#define VM_H

#include <vector>
#include <cstdint>
#include <random>
#include "opcodes.h"

struct VMContext {
    uint32_t regs[16];
    uint32_t sp;
    uint32_t ip;
    uint32_t bp;
    uint32_t flags;
    uint8_t* code;
    uint32_t code_size;
    uint8_t* memory;
    uint32_t memory_size;
    std::vector<uint32_t> stack;
    std::mt19937 rng;
    void* (*syscall_handler)(VMContext* ctx, uint32_t syscall_id, uint32_t* args);
};

void vm_init(VMContext* ctx, uint8_t* code, uint32_t code_size, uint8_t* memory, uint32_t memory_size);
void vm_execute(VMContext* ctx);
uint32_t vm_execute_instruction(VMContext* ctx);
void vm_handle_syscall(VMContext* ctx, uint32_t syscall_id);
std::vector<uint8_t> convert_to_bytecode(const std::vector<uint8_t>& native_code, bool enable_polymorphism = true);
void randomize_vm(VMContext* ctx);

#endif
