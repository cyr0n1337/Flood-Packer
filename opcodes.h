
#ifndef OPCODES_H
#define OPCODES_H

enum VM_OPCODES {
    VM_NOP = 0x00,
    VM_PUSH = 0x01,
    VM_POP = 0x02,
    VM_ADD = 0x03,
    VM_SUB = 0x04,
    VM_MUL = 0x05,
    VM_DIV = 0x06,
    VM_MOD = 0x07,
    VM_AND = 0x08,
    VM_OR = 0x09,
    VM_XOR = 0x0A,
    VM_SHL = 0x0B,
    VM_SHR = 0x0C,
    VM_MOV = 0x0D,
    VM_CMP = 0x0E,
    VM_JMP = 0x0F,
    VM_JE = 0x10,
    VM_JNE = 0x11,
    VM_JG = 0x12,
    VM_JL = 0x13,
    VM_CALL = 0x14,
    VM_RET = 0x15,
    VM_LOAD = 0x16,
    VM_STORE = 0x17,
    VM_PUSHA = 0x18,
    VM_POPA = 0x19,
    VM_SYSCALL = 0x1A,
    VM_CRYPT = 0x1B,
    VM_ROR = 0x1C,
    VM_ROL = 0x1D,
    VM_SWAP = 0x1E,
    VM_RAND = 0x1F,
    VM_DEBUG = 0xFE,
    VM_EXIT = 0xFF
};

enum VM_SYSCALLS {
    SYS_LOADLIBRARY = 0x01,
    SYS_GETPROCADDRESS = 0x02,
    SYS_VIRTUALALLOC = 0x03,
    SYS_VIRTUALFREE = 0x04,
    SYS_VIRTUALPROTECT = 0x05,
    SYS_EXITPROCESS = 0x06
};

#endif
