#include "../include/Semaphore.h"
#include "../include/DataStructure.h"
#include "../include/Thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strSemaphore
{
	int value;
	Queue queue;
	unsigned char* name;
}strSemaphore;


void up(Semaphore* sem)
{
	(((strSemaphore*)(*sem))->value)++;
}

void down(Semaphore* sem)
{
	if((((strSemaphore*)(*sem))->value) > 0)
	{
		(((strSemaphore*)(*sem))->value)--;
	}
	else
	{
		Queue_Insert((((strSemaphore*)(*sem))->queue), ThreadGetCurrentThreadPtr());	
		BlockedCurrentThread();
	}
}

int getSemaphoreValue(Semaphore* sem)
{
	return (((strSemaphore*)(*sem))->value);
}

Semaphore SemaphoreCreate(const unsigned char* name, int value)
{
	strSemaphore* semaphore = NULL;

	semaphore = malloc(sizeof(strSemaphore));
	if(semaphore != NULL)
	{
		semaphore->value = value;
		semaphore->queue = newQueue();
		semaphore->name = (unsigned char*)calloc(strlen(name)+1,sizeof(char));
		strcpy(semaphore->name, name);
	}

	return (void*)semaphore;
}

void destroySemaphore(Semaphore* sem)
{
	free(((strSemaphore*)(*sem))->name);
	DataStructureDestroy(((strSemaphore*)(*sem))->queue);
	free(*sem);
}