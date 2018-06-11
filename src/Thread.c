#include "../include/Thread.h"
#include "../include/Types.h"
#include "../include/DataStructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/MIPS32_M4K.h"


#ifndef MAX_PRIORITY
#define MAX_PRIORITY 7u
#endif

#define STACK_SIZE_DEFAULT 128u
#define ticks_t +0

typedef struct ThreadControlBlock
{
	ThreadAttribute attr;
	unsigned char* name;
	ThreadFunction function;
	ThreadState state;
    unsigned int arrivalCycle;
    unsigned int cpuCycle;
    unsigned int cacheHit;
    unsigned int cacheMiss;
}ThreadControlBlock;


static unsigned qntThreads;
static List ReadyThreads[MAX_PRIORITY];
static List BlockedThreads;
static List SuspendedThreads;
volatile ThreadControlBlock* RunningThread = NULL;
static ThreadControlBlock* candidateThread = NULL;

static unsigned int ThreadTicks ;
static const unsigned timeSlice = 50 ticks_t;
Boolean SwitchThreadRequired; 

static void AddNewThreadReadyList(ThreadControlBlock* Tcb);
extern void* ThreadStackInit(unsigned int* ThreadStackTop, void(Function)(void*), void* parameters);

void ThreadLibInit(void)
{
    unsigned i;
    
   
    for(i = 0; i < MAX_PRIORITY; i++)
    {
        ReadyThreads[i] = newDataStructure();
    }
    BlockedThreads = newDataStructure();
    SuspendedThreads = newDataStructure();
    ThreadTicks = 0;
    SwitchThreadRequired = _FALSE_;
    qntThreads = 0;
}


short ThreadCreate(const unsigned char* name,const ThreadAttribute* threadAtt,ThreadFunction func, Thread* tcb)
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
        newTcb->cacheHit = 0;
        newTcb->cacheMiss;
        newTcb->attr.stackBaseAddress = ThreadStackInit(newTcb->attr.stackBaseAddress,func,NULL);
        AddNewThreadReadyList(newTcb);
        
		return 0;
	}

	return -1;
}

inline Thread __attribute__((always_inline))ThreadGetCurrentThreadPtr(void)
{
	return ((Thread)RunningThread);
}

Boolean ThreadIncrementTicks(void)
{
    volatile const unsigned int Ticks = ThreadTicks + 1;
    Boolean SwitchR = _FALSE_;
    
    ThreadTicks = Ticks;
    
   
    return SwitchR;
}

void ThreadSwitchContext(void)
{
    
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
    DisableInterrupts();
	//RunningThread->state = Blocked;
	//Queue_Insert(BlockedThreads, (void*)RunningThread);
    EnableInterrupts();
}

static void AddNewThreadReadyList(ThreadControlBlock* Tcb)
{
    DisableInterrupts();
    
    if(RunningThread ==  NULL)
    {
        RunningThread = Tcb;
        Tcb->arrivalCycle = _CP0_GET_COUNT();
    }
    else
    {
        if(RunningThread->attr.priority <= Tcb->attr.priority)
        {
            DataStructureInsertBottom(ReadyThreads[Tcb->attr.priority],Tcb);
            SoftwareInterruptRequest();
        }
        else
        {
            
        }
    }
    
    EnableInterrupts();
}