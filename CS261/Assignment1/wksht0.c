#include "ArrayBagStack.h"

void printArr(struct arrayBagStack* b)
{
	for (int i = 0; i < b->count; i++)
	{
		printf("%d ", b->data[i]);
		
	}	
	printf("\n");
}
int main()
{
	struct arrayBagStack myBag;
	initArray(&myBag);

	//Bag

	//Add elements
	TYPE insert = 1;
	for (int i = 0; i < 10; i++)
	{		
		addArray(&myBag, insert);
		insert = insert + 2;
	}
	addArray(&myBag, 1);
	addArray(&myBag, 1);
	//Contains
	TYPE check;
	check = containsArray(&myBag, 17);
	printf("%d\n", check);

	//Print contents
	printArr(&myBag);

	//Remove elements
	removeArray(&myBag, 1);
	removeArray(&myBag, 5);
	removeArray(&myBag, 7);
	removeArray(&myBag, 13);

	printArr(&myBag);

	//Stack
	struct arrayBagStack myStack;
	initArray(&myStack);

	//Push
	TYPE ins = 0;
	for (int i = 0; i <= 10; i++)
	{		
		pushArray(&myStack, ins);
		ins = ins + 2;
	}
	//Check top
	TYPE chk;

	for (int i = 0; i < 10; i++)
	{
		chk = topArray(&myStack);
		printf("%d\n", chk);

		popArray(&myStack);
	}
	


}