#include "memory/mmu/cache.h"
#include "memory/memory.h"

CacheLine Cache[1024];
extern uint8_t hw_mem[];

void init_cache()
{
    for(int i = 0; i < 1024; i++)
         Cache[i].valid_bit = 0;
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	// implement me in PA 3-1
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	// implement me in PA 3-1
// 	uint32_t ret = 0;
	return hw_mem_read(paddr, len);
	return 0;
}

