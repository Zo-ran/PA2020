#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_add(opr_src.val & (0xFFFFFFFF >> 32 - opr_src.data_size), opr_dest.val & (0xFFFFFFFF >> 32 - opr_dest.data_size), opr_dest.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(add, i, rm, v)
make_instr_impl_2op(add, i, rm, b)
make_instr_impl_2op(add, i, a, b)
make_instr_impl_2op(add, i, a, v)
make_instr_impl_2op(add, i, rm, bv)
make_instr_impl_2op(add, r, rm, b)
make_instr_impl_2op(add, r, rm, v)
make_instr_impl_2op(add, rm, r, b)
make_instr_impl_2op(add, rm, r, v)