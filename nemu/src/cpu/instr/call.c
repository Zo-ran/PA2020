#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near)
{
    printf("\e[0;31mfuck %X!!! \e[0m\n", cpu.eip);
    fflush(stdout);
    OPERAND imm, r;
    //get IMM
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    operand_read(&imm);
    printf("\e[0;31mimm: %X!!! \e[0m\n", imm.val);
    fflush(stdout);
    //push eip
    cpu.esp = cpu.esp - 4;
    r.data_size = 32;
    r.type = OPR_MEM;
    r.val = cpu.eip + data_size / 8 + 1;
    r.addr = cpu.esp;
    operand_write(&r);
    printf("\e[0;31mr: %X!!! \e[0m\n", r.val);
    fflush(stdout);
    //change eip
    cpu.eip = imm.val + cpu.eip + data_size / 8 + 1;
    printf("\e[0;31mfuck %X!!! \e[0m\n", cpu.eip);
    fflush(stdout);
    return 0;
}