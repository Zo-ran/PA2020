#include "cpu/instr.h"
#include "cpu/alu.h"
/*
Put the implementations of `and' instructions here.
*/
static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_and(opr_src.val & (0xFFFFFFFF >> (32 - opr_src.data_size)), opr_dest.val & (0xFFFFFFFF >> (32 - opr_dest.data_size)), opr_dest.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(and, i, rm, v)
make_instr_impl_2op(and, i, rm, b)
make_instr_impl_2op(and, i, a, b)
make_instr_impl_2op(and, i, a, v)
//make_instr_impl_2op(and, i, rm, bv)
make_instr_impl_2op(and, r, rm, b)
make_instr_impl_2op(and, r, rm, v)
make_instr_impl_2op(and, rm, r, b)
make_instr_impl_2op(and, rm, r, v)

make_instr_func(and_i2rm_bv)
{
    int len = 1;
    OPERAND imm, rm;
    
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + len;
    operand_read(&imm);
    operand_read(&rm);
    imm.val = sign_ext(imm.val & 0xFF, 8);
  
    alu_and(imm.val, rm.val, data_size);
    return len + 1;
}