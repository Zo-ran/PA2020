#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
make_instr_func(lea)
{
    int len = 1;
    OPERAND m, r;
    m.type = OPR_MEM;
    r.type = OPR_REG;
    m.data_size = r.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &m);
    r.val = m.addr;
    operand_write(&r);
    
    return len;
}
