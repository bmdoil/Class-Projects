
#include <stdlib.h>
#include <assert.h>

# define TYPE int

struct DynArr
{
	TYPE *data;	/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity of the array */
};

void initDynArr(struct DynArr *v, int capacity)
{
	v->data = malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);

	v->size = 0;
	v->capacity = capacity;
	
}
void freeDynArr(struct DynArr *v)
{
	if (v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}



int sizeDynArr(struct DynArr *v)
{
	return v->size;
}

void addDynArr(struct DynArr *v, TYPE val)
{
	/* Check to see if a resize is necessary */
	if (v->size >= v->capacity)
		_setCapacityDynArr(v, 2 * v->capacity);

	v->data[v->size] = val;
	v->size++;
}

void _setCapacityDynArr(struct DynArr *v, int newCap)
{
	struct DynArr* newArr = malloc(sizeof(TYPE) * newCap);
	newArr->capacity = newCap;
	newArr->size = 0;
	for (int i = 0; i < v->capacity; i++)
	{
		newArr->data[i] = v->data[i];
		newArr->size++;
	}
	free(v);
	v = newArr;
}


TYPE getDynArr(struct DynArr * da, int position)
{
	assert(position <= da->size);
	return da->data[position];
}

void putDynArr(struct DynArr * da, int position, TYPE value)
{

	assert(position <= da->capacity);
	da->data[position] = value; //What if this overwrites the value at position? Check?


}

void swapDynArr(struct DynArr* da, int i, int j)
{

	TYPE temp = 0;
	temp = da->data[i];
	da->data[i] = da->data[j];
	da->data[j] = temp;

}

void removeAtDynArr(struct DynArr * da, int index)
{
	for (index; index < da->size; index++) //For i to count, move data down 1 index
	{
		da->data[index] = da->data[index + 1];
	}
	da->size--;
}



