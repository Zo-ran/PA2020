#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_dest);
    opr_src.val += 1;
    operand_write(&opr_dest);
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)