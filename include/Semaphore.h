/************************************/
/*		File: Semaphore.h			*/
/*		Author: Deived William		*/
/*		Date: 20/04/2018			*/
/************************************/
#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_ 

#define MutexCreate(name) 	SemaphoreCreate(name, 1)
#define MutexLock(mutex)	down(mutex)
#define MutexUnLock(mutex)	up(mutex)


typedef void* Semaphore;
typedef void* Mutex;


void up(Semaphore* sem);
void down(Semaphore* sem);
int getSemaphoreValue(Semaphore* sem);
Semaphore* SemaphoreCreate(const unsigned char* name, int value);
void destroySemaphore(Semaphore* sem);

#endif