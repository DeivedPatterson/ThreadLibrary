#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/DataStructure.h"


typedef struct DataStructure
{
	HeadDataStructure beginning;
	HeadDataStructure end;
	unsigned size;
	ptrNode lastNodeAccessed;
	unsigned lastIndexAccessed;
}*ptrDataStructure;


Object newDataStructure(void)
{
	ptrDataStructure dataStruct = NULL;

	dataStruct = (ptrDataStructure)malloc(sizeof(struct DataStructure));

	if(dataStruct != NULL)
	{
		dataStruct->size = 0;
		dataStruct->lastNodeAccessed = NULL;
		dataStruct->lastIndexAccessed = 0;
		dataStruct->beginning = (HeadDataStructure)calloc(1,sizeof(ptrNode));
		dataStruct->end = (HeadDataStructure)calloc(1,sizeof(ptrNode));

		if(dataStruct->beginning == NULL || dataStruct->end == NULL)
		{
			free(dataStruct);
			dataStruct = NULL;
		}
		else
		{
			(*(dataStruct->beginning)) = NULL;
			(*(dataStruct->end)) = NULL;
		}
	}

	return dataStruct;
}

RESPONSE DataStructureInsertTop(Object ds, void* info)
{
	ptrNode newNode = NULL;
	ptrDataStructure dataStruct = (ptrDataStructure)ds;

	if(dataStruct == NULL)
	{
		return NCREATE_DATASTRUCTURE;
	}
	else if(dataStruct->beginning == NULL && dataStruct->end == NULL)
	{
		return NCREATE_DATASTRUCTURE;
	}

	newNode = (ptrNode)malloc(sizeof(struct Node));

	if(newNode == NULL)
		return ALOCATION_FAIL;

	newNode->info = info;
	newNode->index = dataStruct->size;

	newNode->next = *(dataStruct->beginning);
	*(dataStruct->beginning) = newNode;
	if(*(dataStruct->end) == NULL)
		*(dataStruct->end) = newNode;

	dataStruct->size++;

	return SUCCESS;
}



RESPONSE DataStructureInsertBottom(Object ds, void* info)
{

	ptrNode newNode = NULL;
	ptrDataStructure dataStruct = (ptrDataStructure)ds;

	if(dataStruct == NULL)
	{
		return NCREATE_DATASTRUCTURE;
	}
	else if(dataStruct->beginning == NULL && dataStruct->end == NULL)
	{
		return NCREATE_DATASTRUCTURE;
	}

	newNode = (ptrNode)malloc(sizeof(struct Node));

	if(newNode == NULL)
		return ALOCATION_FAIL;

	newNode->info = info;
	newNode->index = dataStruct->size;
	newNode->next = NULL;

	if(*(dataStruct->beginning) == NULL && *(dataStruct->end) == NULL)
	{
		*(dataStruct->beginning) = newNode;
		*(dataStruct->end) = newNode;
	}
	else
	{
		(*(dataStruct->end))->next = newNode;
		(*(dataStruct->end)) = newNode;
	}

	dataStruct->size++;

	return SUCCESS;
}

RESPONSE DataStructureDestroy(Object ds)
{
	ptrNode	scroll;
	ptrDataStructure dataStruct = (ptrDataStructure)ds;

	if(dataStruct == NULL)
	{
		return NCREATE_DATASTRUCTURE;
	}
	else if((dataStruct->beginning == NULL) && (dataStruct->end == NULL))
	{
		free(dataStruct);
		return SUCCESS;
	}
	else if((*(dataStruct->beginning)) == NULL && (*(dataStruct->end) == NULL))
	{
		free(dataStruct->beginning);
		free(dataStruct->end);
		free(dataStruct);
		return SUCCESS;
	}

	scroll = *(dataStruct->beginning);

	while(scroll != NULL)
	{
		*(dataStruct->beginning) = (*(dataStruct->beginning))->next;
		free(scroll);
		scroll = *(dataStruct->beginning);
	}
	free(dataStruct->beginning);
	free(dataStruct->end);
	free(dataStruct);

	return SUCCESS;
}

RESPONSE DataStructureInsert(Object ds, void* info, bool(*compare)(void*,void*))
{

}
RESPONSE DataStructureInsertIndex(Object ds, void* info, unsigned index)
{

}

bool isEmpty(Object ds)
{
	ptrDataStructure dataStruct;

	dataStruct = (ptrDataStructure)ds;

	if(dataStruct == NULL || *(dataStruct->beginning) == NULL)
		return true;

	return false;
}

Object DataStructureRemoveTop(Object ds)
{
	ptrDataStructure dataStruct;
	Object data;

	dataStruct = (ptrDataStructure)ds;

	if((dataStruct ==  NULL) || (dataStruct->beginning == NULL))
		return NULL;
	else if(isEmpty(ds))
		return NULL;

	data = (*(dataStruct->beginning))->info;
	*(dataStruct->beginning) = (*(dataStruct->beginning))->next;
	if(*(dataStruct->beginning) == NULL)
		*(dataStruct->end) = NULL;

	return data;
}

Object DataStructureRemoveBottom(Object ds)
{

}

Object DataStructureRemoveIndex(Object ds, unsigned index)
{

}

Object DataStructureRemove(Object ds, bool(*compare)(void*,void*))
{

}