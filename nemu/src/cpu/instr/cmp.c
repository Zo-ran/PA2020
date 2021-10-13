#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    alu_sub(opr_dest.val, opr_src.val, opr_src.data_size);
}

make_group_impl(cmp_r2rm_b)
