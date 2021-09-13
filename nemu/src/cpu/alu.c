#include "cpu/cpu.h"

void set_PF(uint32_t res)
{
    int even = 0;
    for(int i = 0; i < 8; i++)
    {
        even += (res & 0x00000001);
        res >>= 1;
    }
    cpu.eflags.PF = 1 - even % 2;
}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
    uint32_t res = 0;
    res = dest + src;
    
    uint32_t result = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    uint32_t source = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = result < source;
    

    set_PF(result);
    
    cpu.eflags.ZF = (result == 0);
    
    cpu.eflags.SF = sign(result);
    
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if(sign(source) == sign(dest)) {
        if(sign(source) != sign(result))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
        } else {
                cpu.eflags.OF = 0;
        }
        
    return res & (0xFFFFFFFF >> (32 - data_size));
    
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
    uint32_t res = src + dest + cpu.eflags.CF;
    
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	
	set_PF(res);
	
	cpu.eflags.ZF = (res == 0);
	
	cpu.eflags.CF = (res < src) || (res == src && cpu.eflags.CF == 1);
	
	cpu.eflags.SF = sign(res);
	
	if(sign(src) == sign(dest)) {
        if(sign(src) != sign(res))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
        } else {
                cpu.eflags.OF = 0;
        }
    
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
    uint32_t res = dest - src;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
    cpu.eflags.CF = (res > dest);
    
    set_PF(res);
    
    cpu.eflags.ZF = (res == 0);
        
    cpu.eflags.SF = sign(res);
	
    if(sign(dest) != sign(src)){
        if(sign(dest) != sign(res))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
    }
    else{
        cpu.eflags.OF = 0;
    }
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
    uint32_t res = dest - src - cpu.eflags.CF;
    
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
	set_PF(res);
	
	cpu.eflags.ZF = (res == 0);
	
	cpu.eflags.SF = sign(res);
	
	cpu.eflags.CF = (res > dest) || (res == dest && cpu.eflags.CF == 1);
	
	if(sign(dest) != sign(src)){
        if(sign(dest) != sign(res))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
    }
    else{
        cpu.eflags.OF = 0;
    }
    
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
    //uint64_t csrc = src;
    //uint64_t cdest = dest;
    uint64_t res = src * dest;
    uint64_t temp = res >> data_size;
    if((temp & (0xFFFFFFFF >> (32 - data_size))) == 0){
        cpu.eflags.OF = cpu.eflags.CF = 0;
    } else{
        cpu.eflags.OF = cpu.eflags.CF = 1;
    }
    return res;
    
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
    int64_t csrc = src;
    int64_t cdest = dest;
    int64_t res = csrc * cdest;
    int64_t temp = res >> data_size;
    if((temp & (0xFFFFFFFF >> (32 - data_size))) == 0){
        cpu.eflags.OF = cpu.eflags.CF = 0;
    } else{
        cpu.eflags.OF = cpu.eflags.CF = 1;
    }
    return res;
    
#endif
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
    uint32_t res = dest / src;
    return res;
#endif
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
    int32_t res = dest / src;
    return res;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
    uint32_t res = dest % src;
    return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t res = dest % src;
    return res;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
    uint32_t res = src & dest;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
    cpu.eflags.CF = 0;
    cpu.eflags.OF = 0;
    set_PF(res);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(res);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
    uint32_t res = src ^ dest;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
    cpu.eflags.CF = 0;
    cpu.eflags.OF = 0;
    set_PF(res);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(res);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
    uint32_t res = src | dest;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    
    cpu.eflags.CF = 0;
    cpu.eflags.OF = 0;
    set_PF(res);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(res);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
    src = src % data_size;
    uint32_t res = dest << src;
    dest >>= (data_size - src);
    dest = dest & (0x00000001);
        if(dest != 0)
            cpu.eflags.CF = 1;
        else 
            cpu.eflags.CF = 0;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    set_PF(res);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(res);
    
    return res & (0xFFFFFFFF >> (32 - data_size)); 
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
    src = src % data_size;
    dest = dest & (0xFFFFFFFF >> (32 - data_size)); 
    uint32_t res = dest >> src;
    if(src == 0)
        cpu.eflags.CF = 0;
    else{
        dest = dest >> (src - 1);
        if((dest & (0x00000001)) == 0)
            cpu.eflags.CF = 0;
        else
            cpu.eflags.CF = 1;
    }
    
    uint32_t temp = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    set_PF(temp);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(temp);
   
    return res & (0xFFFFFFFF >> (32 - data_size)); 
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
    src = src % data_size;
    uint32_t now = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    uint32_t mark = sign(now);
    uint32_t final = dest;
    dest = dest & (0xFFFFFFFF >> (32 - data_size));
    for(int i = 0; i < src; i++){
        dest = dest >> 1;
        if(mark == 1){
            if(data_size == 8)
                dest = (dest | 0x00000080);
            else if(data_size == 16)
                dest = (dest | 0x00008000);
            else
                dest = (dest | 0x80000000);
        }
    }
    
    if(src == 0)
        cpu.eflags.CF = 0;
    else{
        final = final >> (src - 1);
        if((final & (0x00000001)) == 0)
            cpu.eflags.CF = 0;
        else
            cpu.eflags.CF = 1;
    }
    uint32_t temp = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    set_PF(temp);
    cpu.eflags.ZF = (temp == 0);
    cpu.eflags.SF = sign(temp);
    
    return dest & (0xFFFFFFFF >> (32 - data_size)); 
    
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
    src = src % data_size;
    uint32_t res = dest << src;
    dest >>= (data_size - src);
    dest = dest & (0x00000001);
        if(dest != 0)
            cpu.eflags.CF = 1;
        else 
            cpu.eflags.CF = 0;
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    set_PF(res);
    cpu.eflags.ZF = (res == 0);
    cpu.eflags.SF = sign(res);
    
    return res & (0xFFFFFFFF >> (32 - data_size)); 
#endif
}