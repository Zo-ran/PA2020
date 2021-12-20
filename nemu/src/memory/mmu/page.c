#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t offset = laddr & (0xfff);
	uint32_t page_idx = (laddr >> 12) & (0x3ff);
	uint32_t dir_idx = (laddr >> 22) & (0x3ff);
	
    uint32_t base = cpu.cr3.pdbr;
	paddr_t dir_addr = (base << 12) + dir_idx * 4;
	PDE pde;
	memcpy(&pde, dir_addr + hw_mem, 4);
	
	assert(pde.present == 1);
	
	uint32_t page_tb_addr = pde.page_frame << 12;
	uint32_t pte_addr = page_tb_addr + page_idx * 4;
	PTE pte;
	memcpy(&pte, pte_addr + hw_mem, 4);
	assert(pte.present == 1);
	paddr_t res_addr = (pte.page_frame << 12) + offset;
	return res_addr;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
