#ifndef __INSTR_CALL_H__
#define __INSTR_CALL_H__
/*
Put the declarations of `call' instructions here.
*/
int call_near(uint32_t eip, uint8_t opcode);
make_instr_func(call_near_indirect);

#endif
