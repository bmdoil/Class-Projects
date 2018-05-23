#include "ArrayBagStack.h"
#include <assert.h>
void initArray(struct arrayBagStack* b)
{	
	b->count = 0;
}

/* Bag Interface Functions */
void addArray(struct arrayBagStack* b, TYPE v)
{
	//Check if full
	if (b->count == 100)
	{
		exit(1); //Stack overflow
	}
	//Set data at count to v
	b->data[b->count] = v;
	//Increment count
	b->count++;
}

int containsArray(struct arrayBagStack* b, TYPE v)
{
	for (int i = 0; i < b->count; i++)
	{
		//If data at i = v, return 
		if EQ(b->data[i], v)
		{
			return b->data[i];
		}
	}
	return NULL;
}

void removeArray(struct arrayBagStack* b, TYPE v)
{
	
	for (int i = 0; i < b->count; i++)
	{
		if EQ(b->data[i], v)
		{
			for (int j = i; j < b->count; j++) //For j = i to count, move data down 1 index
			{
				b->data[i] = b->data[i + 1];
			}
			b->count--;			
		}
	}
}

int sizeArray(struct arrayBagStack * b)
{
	return b->count;
}

/* Stack Interface Functions */
void pushArray(struct arrayBagStack* b, TYPE v)
{
	if (b->count == 100)
	{
		exit(1); //Stack overflow
	}
	b->data[b->count] = v;
	b->count++;
}
TYPE topArray(struct arrayBagStack* b)
{
	assert(isEmptyArray(b) == 0);
	return b->data[b->count - 1];
}
void popArray(struct arrayBagStack * b)
{
	assert(isEmptyArray(b) == 0);
	b->data[b->count - 1] = 0;
	b->count--;
}
int isEmptyArray(struct arrayBagStack * b)
{
	if (b->count == 0)
	{
		return 1;
	}
	return 0;
}