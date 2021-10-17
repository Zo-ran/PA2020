#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_src);
    int temp = cpu.eflags.CF;
    opr_src.val = alu_add(opr_src.val, 1, opr_src.data_size);
    cpu.eflags.CF = temp;
    operand_write(&opr_src);
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)