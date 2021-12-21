#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/
make_instr_func(lgdt) {	    
    printf("\e[0;31mfuck\e[0m\n");
    fflush(stdout);
    int len = 1;
    OPERAND MEM;        
    MEM.data_size = data_size;
    len += modrm_rm(eip + 1, &MEM);
    MEM.data_size = 16;
    operand_read(&MEM);
    cpu.gdtr.limit = MEM.val & 0xffff;
    MEM.data_size = 32;
    MEM.addr += 2;
    operand_read(&MEM);
    cpu.gdtr.base = MEM.val & 0xffffffff;
    
    return len;
}