#include <stdio.h>
#include <stdlib.h>
#include "../include/DataStructure.h"
    

typedef union Integer
{
	int w;
}*Integer;

Integer newInteger(int w)
{
	Integer i;

	i = (Integer)malloc(sizeof(union Integer));
	i->w = w;

	return i;
}

int main(int argc, char const *argv[])
{
	Integer p;

	List lts = newList();
	
	DataStructureInsertTop(lts, newInteger(10));
	
	foreach(p, lts)
	{
		printf("%i\n", p->w);
	}

	p = DataStructureRemoveTop(lts);

	printf("%i\n\n", p->w );

	DataStructureInsertTop(lts, p);

	foreach(p, lts)
	{
		printf("%i\n", p->w);
	}

	return 0;
}