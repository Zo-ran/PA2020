#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/

make_instr_func(call_near)
{
    OPERAND imm, m;
    //get IMM
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = cpu.eip + 1;
    operand_read(&imm);
    
    //push eip
    cpu.esp = cpu.esp - data_size / 8;
    printf("\e[0;31mesp : %X \e[0m\n", cpu.esp);
    fflush(stdout);
    m.data_size = data_size;
    m.type = OPR_MEM;
    m.val = cpu.eip + data_size / 8 + 1;
    m.addr = cpu.esp;
    printf("\e[0;31meip 1: %X \e[0m\n", cpu.eip);
    fflush(stdout);
    operand_write(&m);
    printf("\e[0;31meip 2: %X \e[0m\n", cpu.eip);
    fflush(stdout);


    m.addr = cpu.esp;
    operand_read(&m);
    printf("\e[0;31mmemory : %X \e[0m\n", m.val);
    fflush(stdout);

    
    printf("\e[0;31mimm: %X \e[0m\n", imm.val);
    fflush(stdout);
    
    
    //change eip
    cpu.eip = sign_ext(imm.val, data_size) + cpu.eip + data_size / 8 + 1;
    return 0;
}