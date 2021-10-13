#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    opeprad_read(&opr_src);;
    alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);
}

make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, rm, r, v)
make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, i, r, b)
make_instr_impl_2op(cmp, i, r, v)
make_instr_impl_2op(cmp, a, o, b)
make_instr_impl_2op(cmp, a, o, v)
make_instr_impl_2op(cmp, o, a, b)
make_instr_impl_2op(cmp, o, a, v)