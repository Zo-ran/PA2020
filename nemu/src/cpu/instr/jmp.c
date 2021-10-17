#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = 16;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, 16);
        // thank Ting Xu from CS'17 for finding this bug
        //print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;
        
        return 1 + 16 / 8;
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