#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)
{
    // OPERAND MEM;
    // MEM.data_size = data_size;
    // MEM.type = OPR_MEM;
    // MEM.addr = cpu.esp;
    // MEM.sreg = SREG_SS;
    // operand_read(&MEM);
    // cpu.eip = sign_ext(MEM.val, data_size);
    // cpu.esp += 4;
        OPERAND top;
    top.type=OPR_MEM;
    top.data_size=data_size;
    top.addr=cpu.esp;
    top.sreg=SREG_SS;
    operand_read(&top);
    if(data_size==32)
    {
        cpu.eip=top.val;
        cpu.esp+=0x4;
    }
    if(data_size==16)
    {
        cpu.esp+=0x2;
        cpu.eip=top.val&0xffff;
    }
    return 0;

    return 0;
}

make_instr_func(ret_near_imm16)
{
    OPERAND MEM, IMM;
    MEM.data_size = data_size;
    MEM.type = OPR_MEM;
    MEM.addr = cpu.esp;
    MEM.sreg = SREG_SS;
    IMM.type = OPR_IMM;
    IMM.data_size = 16;
    IMM.addr = eip + 1;
    IMM.sreg = SREG_CS;
    operand_read(&IMM);
    operand_read(&MEM);
    
    cpu.eip = MEM.val;
    cpu.esp += data_size / 8 + IMM.val;
    

    
    return 0;
}