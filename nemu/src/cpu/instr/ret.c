#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)
{
    OPERAND MEM;
    MEM.data_size = data_size;
    MEM.type = OPR_MEM;
    MEM.addr = cpu.ebp + 4;
    operand_read(&MEM);

    cpu.eip = MEM.val;
    printf("\e[0;31mfuck %x\e[0m\n", cpu.eip);
    fflush(stdout);
    assert(0);
    return 0;
}