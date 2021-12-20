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
    // OPERAND imm;
    // imm.sreg = SREG_CS;
    // imm.type = OPR_IMM;
    // imm.data_size=data_size;
    // imm.addr = eip + 1;
    // operand_read(&imm);
    // imm.val = imm.val & (0xFFFFFFFF >> (32 - data_size));
    // cpu.eip = imm.val;
    // imm.addr += data_size / 8;
    // imm.data_size = 16;
    // operand_read(&imm);
    // cpu.segReg[1].val = imm.val;
    // load_sreg(1);
    // return 0;
        OPERAND val;
    val.type=OPR_IMM;
    val.data_size=data_size;
    val.addr=eip+1;
    val.sreg=SREG_CS;
    operand_read(&val);
    switch(data_size)
    {
        case 8:
            val.val=val.val&0xff;
            break;
        case 16:
            val.val=val.val&0xffff;
            break;
        case 32:
            val.val=val.val&0xffffffff;
            break;
        default:
            val.val=val.val;
            break;
    }
    cpu.eip=val.val;
    switch(data_size)
    {
        case 8:
            val.addr=eip+2;
            break;
        case 16:
            val.addr=eip+3;
            break;
        case 32:
            val.addr=eip+5;
            break;
        default:
            val.addr=val.addr;
            break;
    }
    val.type=OPR_IMM;
    val.data_size=16;
    operand_read(&val);
    cpu.segReg[1].val=val.val;
    load_sreg(1);
    return 0;
}