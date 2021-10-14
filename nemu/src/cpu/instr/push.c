#include "cpu/instr.h"

int push(uint32_t eip, uint8_t opcode)
{
    cpu.esp = cpu.esp - 4;
    OPERAND r;
    r.data_size = 32;
    r.type = OPR_MEM;
    r.val = cpu.ebp;
    r.addr = cpu.esp;
    operand_write(&r);
    return 1;
}