#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/

static void instr_execute_1op(){
    
    opr_dest.type = OPR_MEM;
    opr_dest.data_size = data_size;
    opr_dest.addr = cpu.esp;
    
    operand_read(&opr_src);
    opr_dest.val = sign_ext(opr_src.val, data_size);
    operand_write(&opr_dest);
}
