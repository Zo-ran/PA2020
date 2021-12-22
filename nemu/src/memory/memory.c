#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include "memory/mmu/cache.h"

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	for(int i = 0; i < 4; i++) {
	    printf("\e[0;31m%ddata: %x\e[0m\n", i, paddr, hw_mem[paddr]);
	}
    fflush(stdout);  
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	
#ifdef CACHE_ENABLED
		ret = cache_read(paddr, len);
#else
		ret = hw_mem_read(paddr, len);
#endif
	return ret;

}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED
		cache_write(paddr, len, data);
#else
		hw_mem_write(paddr, len, data);
#endif

}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
#ifndef IA32_PAGE
	return paddr_read(laddr, len);
#else
    paddr_t paddr = laddr;
    // printf("\e[0;31mpe: %d, pg: %d\e[0m\n", cpu.cr0.pe, cpu.cr0.pg);
    // fflush(stdout);  
    // printf("\e[0;31mread_addr_before: %x\e[0m\n", paddr);
    if(cpu.cr0.pe && cpu.cr0.pg) {
        if((laddr & 0x00000fff) + len > 0x1000) {   //处理跨页的情况
            uint32_t next_len = (laddr & 0x00000fff) + len - 0x1000;
            uint32_t now_len = len - next_len;
            laddr_t next_laddr = (laddr & 0xfffff000) + 0x1000;
            uint32_t res = paddr_read(page_translate(laddr), now_len);
            res += (paddr_read(page_translate(next_laddr), next_len) << (now_len * 8));
            return res;
        } else {
            paddr = page_translate(laddr);
            return paddr_read(paddr, len);
        }
    } else {
        return paddr_read(laddr, len);
    }
#endif
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
#ifndef IA32_PAGE
	paddr_write(laddr, len, data);
	
#else
    paddr_t paddr = laddr;
    if(cpu.cr0.pe && cpu.cr0.pg) {
        if((laddr & 0x00000fff) + len > 0x1000) {   //处理跨页的情况
            uint32_t next_len = (laddr & 0x00000fff) + len - 0x1000;
            uint32_t now_len = len - next_len;
            laddr_t next_laddr = (laddr & 0xfffff000) + 0x1000;
            paddr_write(page_translate(laddr), now_len, data & (0xffffffff >> (32 - now_len)));
	        paddr_write(page_translate(next_laddr), next_len, data >> (8 * now_len));
        } else {
            paddr = page_translate(laddr);
            paddr_write(paddr, len, data);
        }
    }
#endif
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_read(vaddr, len);
#else
	uint32_t laddr = vaddr;
// 	printf("\e[0;31mread before: %x\e[0m\n", laddr);
//     fflush(stdout);   
	if(cpu.cr0.pe) {
		laddr = segment_translate(vaddr, sreg);
	}
// 	printf("\e[0;31mvaddr: %x\e[0m\n", laddr);
    fflush(stdout);   
	return laddr_read(laddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	laddr_write(vaddr, len, data);
#else
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe) {
		laddr = segment_translate(vaddr, sreg);
	}
	return laddr_write(laddr, len, data);
#endif
}

void init_mem()
{
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);
#ifdef CACHE_ENABLED
	init_cache();
#endif

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
