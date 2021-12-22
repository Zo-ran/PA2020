#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
	printf("\e[0;31mbase: %x\e[0m\n", cpu.segReg[sreg].base);
    fflush(stdout);   
    return cpu.segReg[sreg].base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
    uint32_t offset = cpu.segReg[sreg].index + cpu.gdtr.base;
	SegDesc *segdesc = (SegDesc *)hw_mem + offset;
	segdesc->val[0] = laddr_read(offset, 4);
	segdesc->val[1] = laddr_read(offset + 4, 4);
	cpu.segReg[sreg].base = (segdesc->base_15_0 & 0xffff) + ((segdesc->base_23_16 & 0xff) << 16) + ((segdesc->base_31_24 & 0xff) << 24);
	cpu.segReg[sreg].base = 0;
	cpu.segReg[sreg].limit = (segdesc->limit_15_0 & 0xffff) + ((segdesc->limit_19_16 & 0xf) << 16);
	cpu.segReg[sreg].type = (segdesc->type & 0xf) + ((segdesc->segment_type & 0x1) << 4);
	cpu.segReg[sreg].privilege_level = segdesc->privilege_level;
	cpu.segReg[sreg].soft_use = segdesc->soft_use & 0x1;
}
