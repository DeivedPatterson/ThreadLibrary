#include <stdio.h>
#include <stdlib.h>
//#include "../include/Semaphore.h"


typedef struct ThreadControlBlock
{
	unsigned int* stackBaseAddress;
	unsigned int* stackLimitAddress;
	//tid_t id;
	unsigned short priority;
	unsigned int stackWordSize;
	
}ThreadControlBlock;

int main(int argc, char const *argv[])
{
	ThreadControlBlock* t;
	void* p;
	unsigned *ptr;

	t = (ThreadControlBlock*)malloc(sizeof(ThreadControlBlock));
	t->stackLimitAddress = (unsigned*)calloc(10,sizeof(unsigned));
	t->stackBaseAddress = &(t->stackLimitAddress[9]);
	p = t;

	ptr = (unsigned*)p;
	ptr++;
	*ptr = 9;
//	printf("%u\n", *ptr);
	printf("%u\n", *(t->stackBaseAddress));
	free(t);

	return 0;
}