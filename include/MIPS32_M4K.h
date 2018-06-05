/************************************/
/*		File: MIPS32_M4K.h          */
/*		Author: Deived William		*/
/*		Date: 20/04/2018			*/
/************************************/

#ifndef MIPS32_M4K_H
#define	MIPS32_M4K_H
#include <p32xxxx.h>

inline unsigned int __attribute__((nomips16,always_inline)) EnableInterrupts(void);
inline unsigned int __attribute__((nomips16,always_inline)) DisableInterrupts(void);
void __attribute__((nomips16)) KSeg0Cacheable(void);
void __attribute__((nomips16)) KSeg0Uncached(void);
#endif	/* MIPS32_M4K_H */

