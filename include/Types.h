/************************************/
/*		File: Types.h				*/
/*		Author: Deived William		*/
/*		Date: 20/04/2018			*/
/************************************/
#ifndef TYPES_H_
#define TYPES_H_

#define True    1u
#define False   0u

typedef unsigned short tid_t;
typedef void* Thread;

typedef enum
{
    _FALSE_,
    _TRUE_          
}Boolean;

typedef void (*ThreadFunction)(void* parameters);

#endif