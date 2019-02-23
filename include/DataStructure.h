/************************************/
/*		File: DataStructure.h		*/
/*		Author: Deived William		*/
/*		Date: 03/04/2018			*/
/************************************/


#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define newList() 						newDataStructure()
#define newQueue()						newDataStructure()
#define newStack()						newDataStructure()
#define Stack_Pop(dataStruct)			DataStructureRemoveBottom(dataStruct)
#define Stack_Push(dataStruct, info)	DataStructureInsertBottom(dataStruct, info)
#define Queue_Insert(dataStruct, info)	DataStructureInsertTop(dataStruct, info)
#define Queue_Remove(dataStruct)		DataStructureRemoveBottom(dataStruct)

#define toCircularChained(dataStruct)
#define toChained(dataStruct)

#define foreach(ptr, dataStruct) \
   for(ptrNode scroll = *(*((void***)dataStruct)); scroll != NULL?ptr = scroll->info:0,scroll != NULL; scroll = scroll->next) 



typedef enum 
{
	SUCCESS,
	ALOCATION_FAIL,
	NCREATE_DATASTRUCTURE
}RESPONSE;

typedef struct Node
{
	struct Node* next;
	struct Node* previous;
	void* info;
	unsigned index;	
}*ptrNode;

typedef ptrNode* HeadDataStructure;



typedef void *Object;
typedef void* Queue;
typedef void* Stack;
typedef void* List;

Object newDataStructure(void);
RESPONSE DataStructureDestroy(Object ds);
bool isEmpty(Object ds);
RESPONSE DataStructureInsertTop(Object ds, void* info);
RESPONSE DataStructureInsertBottom(Object ds, void* info);
RESPONSE DataStructureInsert(Object ds, void* info, bool(*compare)(void*,void*));
RESPONSE DataStructureInsertIndex(Object ds, void* info, unsigned index);
Object DataStructureRemoveTop(Object ds);
Object DataStructureRemoveBottom(Object ds);
Object DataStructureRemoveIndex(Object ds, unsigned index);
Object DataStructureRemove(Object ds, bool(*compare)(void*,void*));

#ifdef __cplusplus
}
#endif


#endif