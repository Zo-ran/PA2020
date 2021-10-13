#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_add(opr_src.val, opr_dest.val, opr_src.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(add, r, rm, v)