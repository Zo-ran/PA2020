#include "cpu/instr.h"

static void instr_execute_1op(){
    
    cpu.esp -= 4;
    
    opr_dest.type = OPR_MEM;
    opr_dest.data_size = data_size;
    opr_dest.addr = cpu.esp;
    
    operand_read(&opr_src);
    opr_dest.val = sign_ext(opr_src.val, data_size);
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, rm, v)

make_instr_func(push_r_v)
{
    cpu.esp -= 4;
    
    OPERAND r, m;
    r.type = OPR_REG;
    r.data_size = data_size;
    r.addr = opcode & 0x7;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    
    operand_read(&r);
    m.val = r.val & (0xFFFFFFFF >> (32 - data_size));
    operand_write(&m);
    return 1;
}
