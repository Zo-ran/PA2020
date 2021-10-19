#include "cpu/instr.h"
/*
Put the implementations of `not' instructions here.
*/
make_instr_func(not_rm_b)
{
    int len = 1;
    OPERAND rm;
    rm.data_size = 8;
    len += modrm_rm(eip + 1, &rm);
    rm.val = sign_ext(~rm.val & 0xFF, 8);
    operand_write(&rm);
    return len;
}

make_instr_func(not_rm_v)
{
    int len = 1;
    OPERAND rm;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    rm.val = sign_ext(~rm.val & (0xFFFFFFFF >> (32 - data_size)), data_size);
    operand_write(&rm);
    return len;
}