#include "memory/mmu/cache.h"

CacheLine Cache[1024];

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
	return hw_mem_read(paddr, len);
	return 0;
}

