
#include "vm.h"
#include <stdexcept>
#include <cstring>
#include "anti_debug.h"

void vm_init(VMContext* ctx, uint8_t* code, uint32_t code_size, uint8_t* memory, uint32_t memory_size) {
    memset(ctx, 0, sizeof(VMContext));
    ctx->regs[0] = 0;
    ctx->sp = 0;
    ctx->ip = 0;
    ctx->bp = 0;
    ctx->flags = 0;
    ctx->code = code;
    ctx->code_size = code_size;
    ctx->memory = memory;
    ctx->memory_size = memory_size;
    ctx->stack.reserve(2048);
    ctx->rng.seed(GetTickCount() ^ (uint32_t)ctx);
    for (int i = 1; i < 16; i++) ctx->regs[i] = ctx->rng();
}

uint32_t vm_execute_instruction(VMContext* ctx) {
    if ((ctx->ip % 97) == 0) {
        if (check_debugger()) {
            ctx->regs[0] = 0xDEADBEEF;
            return VM_EXIT;
        }
    }
    uint8_t opcode = ctx->code[ctx->ip++];
    uint8_t operand1, operand2;
    uint32_t immediate, address;
    switch (opcode) {
        case VM_CRYPT: {
            uint32_t key = ctx->regs[ctx->code[ctx->ip++]];
            uint32_t src_addr = ctx->regs[ctx->code[ctx->ip++]];
            uint32_t dst_addr = ctx->regs[ctx->code[ctx->ip++]];
            uint32_t length = ctx->regs[ctx->code[ctx->ip++]];
            for (uint32_t i = 0; i < length; i++) {
                if (src_addr + i < ctx->memory_size && dst_addr + i < ctx->memory_size) {
                    ctx->memory[dst_addr + i] = ctx->memory[src_addr + i] ^ (key & 0xFF);
                    key = (key >> 8) | (key << 24);
                }
            }
            break;
        }
        case VM_DEBUG: {
            if (check_debugger()) {
                ctx->regs[0] += ctx->rng();
                ctx->flags ^= 0xFFFFFFFF;
            }
            break;
        }
        case VM_SYSCALL: {
            uint32_t syscall_id = ctx->code[ctx->ip++];
            uint32_t arg_count = ctx->code[ctx->ip++];
            uint32_t args[4] = {0};
            for (uint32_t i = 0; i < arg_count && i < 4; i++) args[i] = ctx->regs[ctx->code[ctx->ip++]];
            if (ctx->syscall_handler) ctx->regs[0] = (uint32_t)ctx->syscall_handler(ctx, syscall_id, args);
            break;
        }
    }
    return opcode;
}

void vm_execute(VMContext* ctx) {
    while (ctx->ip < ctx->code_size) {
        uint8_t opcode = vm_execute_instruction(ctx);
        if (opcode == VM_EXIT) break;
    }
}
