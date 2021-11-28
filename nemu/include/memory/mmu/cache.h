#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"


typedef struct {
    bool valid_bit;    //标志位，用于判断Cashline是否有效
    uint32_t mark;      //标记部分，取低19位
    uint8_t data[64];
} CacheLine;

#ifdef CACHE_ENABLED
// init the cache
void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len);

#endif

#endif
