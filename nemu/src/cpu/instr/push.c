#include "cpu/instr.h"

static void instr_execute_1op(){
    
    cpu.esp -= data_size / 8;
    
    opr_dest.type = OPR_MEM;
    opr_dest.data_size = data_size;
    opr_dest.addr = cpu.esp;
    
    operand_read(&opr_src);
    opr_dest.val = sign_ext(opr_src.val + 1, data_size);
    operand_write(&opr_dest);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, rm, v)
