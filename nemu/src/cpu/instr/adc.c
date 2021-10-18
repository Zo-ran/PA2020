#include "cpu/instr.h"
#include"cpu/alu.h"
/*
Put the implementations of `adc' instructions here.
*/
static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_add(opr_src.val & (0xFFFFFFFF >> (32 - opr_src.data_size)), opr_dest.val & (0xFFFFFFFF >> (32 - opr_dest.data_size)), opr_dest.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(adc, i, rm, v)
make_instr_impl_2op(adc, i, rm, b)
make_instr_impl_2op(adc, i, a, b)
make_instr_impl_2op(adc, i, a, v)
make_instr_impl_2op(adc, i, rm, bv)
make_instr_impl_2op(adc, r, rm, b)
make_instr_impl_2op(adc, r, rm, v)
make_instr_impl_2op(adc, rm, r, b)
make_instr_impl_2op(adc, rm, r, v)