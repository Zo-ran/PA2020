#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_src.val = opr_src.val & (0xFFFFFFFF >> (32 - data_size));
    opr_dest.val = opr_dest.val & (0xFFFFFFFF >> (32 - data_size));
    alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);    
}

make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, i, a, v)
make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, rm, r, v)

make_instr_func(cmp_i2a_b)
{
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.data_size = 8;
    operand_read(&imm);
    
    alu_sub(imm.val, cpu.eax, 8);
    return 2;
}

make_instr_func(cmp_i2rm_bv)
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
  
    alu_sub(imm.val, rm.val, data_size);
    return len + 1;
}