#include "cpu/instr.h"
#include"cpu/alu.h"

static void instr_execute_2op(){
    operand_read(&opr_src);
    opeprad_read(&opr_src);;
    alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);
}