#include "../include/MIPS32_M4K.h"


inline unsigned int __attribute__((nomips16,always_inline)) EnableInterrupts(void)
{
    unsigned int status;
    
    asm volatile("ei %0" : "=r"(status));
    
    return status;
}

inline unsigned int __attribute__((nomips16,always_inline)) DisableInterrupts(void)
{
    unsigned status;
    
    asm volatile("di %0" : "=r"(status));
    
    return status;
}

void __attribute__((nomips16)) KSeg0Cacheable(void)
{
    volatile register unsigned long temp;
    
    asm volatile("mfc0 %0,$16,0": "=r"(temp));
    temp = (temp&0xFFFFFFF8)|3;
    asm volatile("mtc0 %0,$16,0" :: "r"(temp));
}

void __attribute__((nomips16)) KSeg0Uncached(void)
{
    volatile register unsigned long temp;
    
    asm volatile("mfc0 %0,$16,0": "=r"(temp));
    temp = (temp&0xFFFFFFF8)|2;
    asm volatile("mtc0 %0,$16,0" :: "r"(temp));  
}

void __attribute__((nomips16)) SoftwareInterruptRequest(void)
{
    volatile register unsigned long temp;
    
    asm volatile("mfc0 %0,$13,0" : "=r"(temp));
    temp = temp | (unsigned long)(1 << 8);
    asm volatile("mtc0 %0,$13,0" :: "r"(temp));
}