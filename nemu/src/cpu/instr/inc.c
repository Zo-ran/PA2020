#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_dest);
    int temp = cpu.eflags.CF;
    opr_dest.val = alu_add(opr_dest.val, 1, opr_dest.data_size);
    cpu.eflags.CF = temp;
    operand_write(&opr_dest);
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)