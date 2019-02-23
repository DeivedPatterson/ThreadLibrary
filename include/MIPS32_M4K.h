/************************************/
/*		File: MIPS32_M4K.h          */
/*		Author: Deived William		*/
/*		Date: 20/04/2018			*/
/************************************/

#ifndef MIPS32_M4K_H
#define	MIPS32_M4K_H
#include <p32xxxx.h>

#include "MIPS32_M4K.h"

#include "Config.h"


#define IPL_BITS    0x003F0000
#define IPL_SHIFT   10UL

#define DISABLE_INTERRUPTS()                                                        \
{                                                                                   \
    unsigned int CP0_Status;                                                        \
                                                                                    \
    CP0_Status = _CP0_GET_STATUS();                                                 \
    CP0_Status &= ~IPL_BITS;                                                        \
    _CP0_SET_STATUS((CP0_Status|(MAX_SYSCALL_INTERRUPT_PRIORITY << IPL_SHIFT)));    \
}

#define ENABLE_INTERRUPTS()                                                         \
{                                                                                   \
    unsigned int CP0_Status;                                                        \
                                                                                    \
    CP0_Status = _CP0_GET_STATUS();                                                 \
    CP0_Status &= ~IPL_BITS;                                                        \
    _CP0_SET_STATUS(CP0_Status);                                                    \
}

inline unsigned int __attribute__((nomips16,always_inline)) EnableInterrupts(void);
inline unsigned int __attribute__((nomips16,always_inline)) DisableInterrupts(void);
void __attribute__((nomips16)) KSeg0Cacheable(void);
void __attribute__((nomips16)) KSeg0Uncached(void);
void __attribute__((nomips16)) SoftwareInterruptRequest(void);
#endif	/* MIPS32_M4K_H */

