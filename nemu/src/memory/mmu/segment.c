#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
    return cpu.segReg[sreg].base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
    uint32_t offset = cpu.segReg[sreg].index + cpu.gdtr.base;
	SegDesc *segdesc = hw_mem + offset;
	segdesc->val[0] = laddr_read(offset, 4);
	segdesc->val[1] = laddr_read(offset + 4, 4);
	cpu.segReg[sreg].base = (segdesc->base_15_0 & 0xffff) + ((gset->base_23_16 & 0xff) << 16) + ((get->base_31_24 & 0xff) << 24);
	cpu.segReg[sreg].limit = (get->limit_15_0 & 0xffff) + ((get->limit_19_16 & 0xf) << 16);
	cpu.segReg[sreg].type = (get->type & 0xf) + ((get->segment_type & 0x1) << 4);
	cpu.segReg[sreg].privilege_level = get->privilege_level;
	cpu.segReg[sreg].soft_use = get->soft_use & 0x1;
}
