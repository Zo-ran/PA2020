#include "memory/mmu/cache.h"
#include "memory/memory.h"

CacheLine Cache[1024];
extern uint8_t hw_mem[];    //大小为128 * 1024 * 1024

void init_cache()
{
    for(int i = 0; i < 1024; i++)
         Cache[i].valid_bit = 0;
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	uint32_t offset = paddr & 0x3f;
	uint32_t group = (paddr >> 6) & 0x7f;
	uint32_t mark = (paddr >> 13) & 0x7ffff;
	bool hit = false;

	for(int i = 0; i < 8; i++) {
		if(Cache[group * 8 + i].mark == mark && Cache[group * 8 + i].valid_bit) {
			hit = true;
			if(offset + len <= 64) {       //越行的话，写cache的时候会有不同
				memcpy(hw_mem + paddr, &data, len);   //更新主存
				memcpy(Cache[group * 8 + i].data + offset, &data, len);
			} else {
				size_t now_len = 64 - offset;
				size_t next_len = len - now_len;
				cache_write(paddr, now_len, data);
				cache_write(paddr + now_len, next_len, data >> (8 * now_len));
			}
			break;
		}
	}

	if(!hit) {
		memcpy(hw_mem + paddr, &data, len);   
	}
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;      //返回的数据ret
	uint32_t offset = paddr & 0x3f;       //块内地址offset
	uint32_t group = (paddr >> 6) & 0x7f;      //组号group
	uint32_t mark = (paddr >> 13) & 0x7ffff;      //标记mark
	bool hit = false;         //hit用于判断是否命中

	for(int i = 0; i < 8; i++) {
		if(Cache[group * 8 + i].mark == mark && Cache[group * 8 + i].valid_bit) {//判断是否标记相同且valid
			hit = true;	                          //命中
			if(offset + len <= 64) {              //判断是否越行
				for(int j = len - 1; j >= 0; j--) {
					ret <<= 8;                         //注意小端方式
					ret += Cache[group * 8 + i].data[offset + j];
				}
				break;
			} else {                            //如果越行，递归的使用两次cache_read
				size_t next_len = offset + len - 64;    //下一行需要读入的长度
				size_t now_len = 64 - offset;           //这一行需要读入的长度
				paddr_t next_paddr = now_len + paddr;
				ret += cache_read(next_paddr, next_len);   //小端方式，先读入下一行
				ret <<= (now_len * 8);     //小端方式，为低位移出空间
				ret += cache_read(paddr, now_len);    //读此行的数据
				break;
			}
		}
	}

	bool find = false;      //find用于判断这个组还有无空行
	if(!hit) {
		for(int i = 0; i < 8; i++) {
			if(Cache[8 * group + i].valid_bit == false) {
				find = true;
				Cache[8 * group + i].valid_bit = 1;
				Cache[8 * group + i].mark = mark;
				memcpy(Cache[8 * group + i].data, paddr + hw_mem - offset, 64);
				ret = cache_read(paddr, len);
				break;
			}
		}
	}

	if(!hit && !find) {           //如果没有空行，随机替换一行，为了偷懒，这里直接替换第0行
		Cache[8 * group].valid_bit = true;
		Cache[8 * group].mark = mark;
		memcpy(Cache[8 * group].data, paddr - offset + hw_mem, 64);
	}

	return ret;
}

