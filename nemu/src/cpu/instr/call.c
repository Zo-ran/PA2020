#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_near)
{
    OPERAND imm, m;
    //get IMM
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = cpu.eip + 1;
    operand_read(&imm);
    
    //push eip
    cpu.esp = cpu.esp - 4;
    m.data_size = 32;
    m.type = OPR_MEM;
    m.val = cpu.eip + 5;
    m.addr = cpu.esp;
    operand_write(&m);
    
    //change eip
    cpu.eip = sign_ext(imm.val, data_size) + cpu.eip + data_size / 8 + 1;
    return 0;
}