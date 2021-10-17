#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
make_instr_func(lea)
{
    OPERAND r, m;
    m.data_size = r.data_size = data_size;
    int len = 1;
    len += modrm_r_rm(eip + 1, &r, &m);
    operand_read(&r);
    r.val = m.val;
    operand_write(&m);
    
    return len;
     
}