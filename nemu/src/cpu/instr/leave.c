#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave)
{
    cpu.esp = cpu.ebp;
    OPERAND m;
    m.addr = cpu.esp;
    m.type = OPR_MEM;
    m.data_size = data_size;
    operand_read(&m);
    cpu.ebp = m.val;
    
    return 1;
}