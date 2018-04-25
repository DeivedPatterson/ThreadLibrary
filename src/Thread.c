#include "../include/Thread.h"
#include "../include/Types.h"
#include <stdio.h>
#include <stdlib.h>


#ifndef MAX_PRIORITY
#define MAX_PRIORITY 7u
#endif

#define STACK_SIZE_DEFAULT 128u


typedef struct ThreadControlBlock
{
	ThreadAttribute attr;
	unsigned char* name;
	ThreadFunction function;
	ThreadState state;
}ThreadControlBlock;

static unsigned qntThreads;
static List ReadyThreads[MAX_PRIORITY];
static List BlockedThreads;
static List SuspendedThreads;
volatile ThreadControlBlock* RunningThread = NULL;


short ThreadCreate(const unsigned char* name,const ThreadAttribute* threadAtt,ThreadFunction func,const Thread* tcb)
{
	ThreadControlBlock* newTcb = NULL;

	newTcb = (ThreadControlBlock*)malloc(sizeof(ThreadControlBlock));

	if(newTcb != NULL)
	{
		if(threadAtt == NULL)
		{
			newTcb->attr.id = qntThreads;
			newTcb->attr.priority = 1;
			newTcb->attr.stackWordSize = STACK_SIZE_DEFAULT;
			newTcb->attr.stackLimitAddress = (unsigned int*)calloc(STACK_SIZE_DEFAULT, sizeof(unsigned int));
			newTcb->attr.stackBaseAddress = &(newTcb->attr.stackLimitAddress[STACK_SIZE_DEFAULT-1]);
		}
		else
		{
			newTcb->attr.id = threadAtt->id;
			newTcb->attr.priority = threadAtt->priority;
			newTcb->attr.stackWordSize = threadAtt->stackWordSize;
			newTcb->attr.stackLimitAddress = threadAtt->stackLimitAddress;
			newTcb->attr.stackBaseAddress = threadAtt->stackBaseAddress;
		}

		newTcb->name = (char*)calloc(strlen(name)+1,sizeof(char));
		strcpy(newTcb->name,name);
		newTcb->state = Ready;
		newTcb->function = func;
		*tcb = (void*)newTcb;
		qntThreads++;
		Queue_Insert(ReadyThreads[newTcb->attr.priority], newTcb);

		return 0;
	}

	return -1;
}

inline Thread __attribute__((always_inline))ThreadGetCurrentThreadPtr(void)
{
	return ((Thread)RunningThread);
}

void ThreadWaitTicks(const unsigned int ticks)
{

}

void ThreadDelayMs(const unsigned int time)
{

}

void ThreadBlocked(Thread* threadToBlocked)
{

}

void ThreadResume(Thread* threadToResume)
{

}

void BlockedCurrentThread()
{
	RunningThread->state = Blocked;
	Queue_Insert(BlockedThreads, (void*)RunningThread);
}