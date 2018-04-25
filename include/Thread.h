/************************************/
/*		File: Thread.h				*/
/*		Author: Deived William		*/
/*		Date: 20/04/2018			*/
/************************************/

#ifndef THREAD_H_
#define THREAD_H_

#include "types.h"

typedef enum ThreadState
{
	Running = 0,
	Ready,
	Blocked,
	Suspended,
}ThreadState;

typedef struct ThreadAttribute
{
	unsigned int* stackBaseAddress;
	unsigned int* stackLimitAddress;
	tid_t id;
	unsigned short priority;
	unsigned int stackWordSize;
}ThreadAttribute;

typedef void* (*ThreadFunction)(void* parameters);

short ThreadCreate(const unsigned char* name, const ThreadAttribute* threadAtt, ThreadFunction func, const Thread* tcb);

void ThreadWaitTicks(const unsigned int ticks);
void ThreadDelayMs(const unsigned int time);
void ThreadBlocked(Thread* threadToBlocked);
void ThreadResume(Thread* threadToResume);
inline Thread __attribute__((always_inline))ThreadGetCurrentThreadPtr(void);
void BlockedCurrentThread();

#endif