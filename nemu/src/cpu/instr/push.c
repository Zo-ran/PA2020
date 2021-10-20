#include "cpu/instr.h"

make_instr_func(push_r_v)
{
    cpu.esp -= 4;
    
    OPERAND r, m;
    r.type = OPR_REG;
    r.data_size = data_size;
    r.addr = opcode & 0x7;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    
    operand_read(&r);
    m.val = sign_ext(r.val & (0xFFFFFFFF >> (32 - data_size)), data_size);
    operand_write(&m);
    return 1;
}

make_instr_func(push_i_b)
{
    cpu.esp -= 4;
    
    OPERAND imm, m;
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + 1;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    
    operand_read(&imm);
    m.val = sign_ext(imm.val & 0xFF, 8);
    operand_write(&m);
    return 2;
}

make_instr_func(push_rm_v)
{
    int len = 1;
    cpu.esp -= 4;
    
    OPERAND rm, m;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    m.addr = cpu.esp;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.val = rm.val;
    /*printf("\e[0;31mrm.addr: %x\e[0m\n", rm.addr);
    fflush(stdout);
    printf("\e[0;31mm.val: %x\e[0m\n", m.val);
    fflush(stdout);
    assert(0);*/
    operand_write(&m);
    return len;
}
/*static void instr_execute_1op()
{
    cpu.esp -= 4;
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    opr_dest.data_size = data_size;
    operand_read(&opr_src);
    opr_dest.val = sign_ext(opr_src.val, data_size);
    operand_write(&opr_dest);
}*/

// make_instr_impl_1op(push, i, b);
// make_instr_impl_1op(push, r, v);
// make_instr_impl_1op(push, rm, v);