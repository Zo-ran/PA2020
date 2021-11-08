#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)
{
    OPERAND MEM;
    MEM.data_size = data_size;
    MEM.type = OPR_MEM;
    MEM.addr = cpu.esp;
    operand_read(&MEM);
    
    cpu.eip = sign_ext(MEM.val, data_size);
    cpu.esp += 4;

    return 0;
}

make_instr_func(ret_near_imm16)
{
    OPERAND MEM, IMM;
    MEM.data_size = data_size;
    MEM.type = OPR_MEM;
    MEM.addr = cpu.esp;
    IMM.type = OPR_IMM;
    IMM.data_size = 16;
    IMM.addr = eip + 1;
    operand_read(&IMM);
    operand_read(&MEM);
    
    cpu.eip = MEM.val;
    cpu.esp += data_size / 8 + IMM.val;
    

    
    return 0;
}