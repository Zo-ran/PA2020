#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)
{
    OPERAND MEM;
    MEM.data_size = data_size;
    MEM.type = OPR_MEM;
    MEM.addr = cpu.esp;
    operand_read(&MEM);
    printf("\e[0;31mfuck %x\e[0m\n", eip);
    fflush(stdout);
    assert(0);
    cpu.eip = MEM.val;
    return 0;
}