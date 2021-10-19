#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
make_instr_func(pop_r_v)
{
    /*OPERAND r, m;
    r.type = OPR_REG;
    r.data_size = data_size;
    r.addr = opcode & 0x7;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    
    operand_read(&m);
    r.val = sign_ext(m.val & (0xFFFFFFFF >> (32 - data_size)), data_size);
    operand_write(&r);
    
    cpu.esp += 4;*/
    return 1;
}