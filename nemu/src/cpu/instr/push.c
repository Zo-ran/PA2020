#include "cpu/instr.h"

int push_ebp(uint32_t eip, uint8_t opcode)
{        printf("\e[0;31mfuck %x\e[0m\n", cpu.eip);
    fflush(stdout);
    assert(0);
    cpu.esp = cpu.esp - 4;
    OPERAND r;
    r.data_size = 32;
    r.type = OPR_MEM;
    r.val = cpu.ebp;
    r.addr = cpu.esp;
    operand_write(&r);
        printf("\e[0;31mfuck \e[0m\n");
    fflush(stdout);
    assert(0);
    return 1;
}