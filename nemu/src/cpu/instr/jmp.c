#include "cpu/instr.h"

make_instr_func(jmp_near)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, data_size);
    // thank Ting Xu from CS'17 for finding this bug
    //print_asm_1("jmp", "", 1 + data_size / 8, &rel);

    cpu.eip += offset;
    
    return 1 + data_size / 8;
}


make_instr_func(jmp_short)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.data_size = 8;
    rel.addr = eip + 1;
    
    operand_read(&rel);
    
    int offset = sign_ext(rel.val, 8);
    cpu.eip += offset;
    
    
    return 2;
    
}

make_instr_func(jmp_near_indirect)
{
    OPERAND rm;
    rm.data_size = data_size;
    modrm_rm(eip + 1, &rm);
    operand_read(&rm);
    
    cpu.eip = sign_ext(rm.val & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
    return 0;
}

make_instr_func(jmp_far_imm) {
            printf("\e[0;31mfuckyoubitch\e[0m\n");
    fflush(stdout);
    OPERAND imm;
    imm.sreg = SREG_CS;
    imm.type = OPR_IMM;
    imm.data_size=data_size;
    imm.addr = eip + 1;
    operand_read(&imm);
    imm.val = imm.val & (0xFFFFFFFF >> (32 - data_size));
    cpu.eip = imm.val;
    imm.addr += data_size / 8;
    imm.data_size = 16;
    operand_read(&imm);
    cpu.segReg[1].val = imm.val;
    load_sreg(1);
    return 0;
}