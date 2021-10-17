#include "cpu/instr.h"
#include "cpu/alu.h"
/*
Put the implementations of `inc' instructions here.
*/
make_instr_func(inc_r_v)
{
    OPERAND r;
    r.data_size = data_size;
    r.type = OPR_REG;
    r.addr = opcode & 0x7;
    int temp = cpu.eflags.CF;
    
    operand_read(&r);
    r.val = alu_add(r.val, 1, r.data_size);
    operand_write(&r);
    cpu.eflags.CF = temp;
    return 1;
}

make_instr_func(inc_rm_v)
{
    OPERAND rm;
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    int temp = cpu.eflags.CF;
    
    operand_read(&rm);
    rm.val = alu_add(rm.val, 1, rm.data_size);
    operand_write(&rm);
    cpu.eflags.CF = temp;
    return len;
}