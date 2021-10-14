#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near)
{
    cpu.eip = cpu.ebp + 4;
    return 0;
}