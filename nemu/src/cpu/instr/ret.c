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
    
    cpu.eip = MEM.val & (0xFFFFFFFF >> (32 - data_size));
    cpu.esp += data_size / 8;
    printf("\e[0;31mfuck %X\e[0m\n", cpu.eip);
    assert(0);
    return 0;
}