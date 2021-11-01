#include "cpu/instr.h"
#include"cpu/alu.h"
/*
Put the implementations of `sub' instructions here.
*/
static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = sign_ext(opr_dest.val, opr_dest.data_size);
    opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
    opr_dest.val = alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);
    operand_write(&opr_dest);
}
make_instr_impl_2op(sub, i, rm, bv)
make_instr_impl_2op(sub, i, rm, v)
make_instr_impl_2op(sub, i, rm, b)
make_instr_impl_2op(sub, i, a, b)
make_instr_impl_2op(sub, i, a, v)
make_instr_impl_2op(sub, r, rm, b)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, rm, r, b)
make_instr_impl_2op(sub, rm, r, v)

/*make_instr_func(sub_i2rm_bv) {
    OPERAND imm, rm;
    int len = 1;
    // read rm
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    operand_read(&rm);
    
    //read imm
    imm.data_size = 8;
    imm.addr = eip + len;
    imm.type = OPR_IMM;
    operand_read(&imm);
    imm.val = sign_ext(imm.val, 8);
    
    // sub
    rm.val = alu_sub(imm.val, rm.val, 8);
    operand_write(&rm);
    
    return len + 1;
}*/