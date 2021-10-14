#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near)
{
    OPERAND imm, r;
    //get IMM
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    operand_read(&imm);
    //push eip
    cpu.esp = cpu.esp - 4;
    r.data_size = 32;
    r.type = OPR_MEM;
    r.val = eip;
    r.addr = cpu.esp;
    operand_write(&r);
    //change eip
    cpu.eip += imm.val;
    
}