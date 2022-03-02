/* ********************************************************************
 * Purpose : Creates and handles all linkedlist operations :
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include "linkedlist.h"
 #include "string.h"

/* DESCRIPTION :    Create linklist... */
LinkedList* createLinkedList()
{
	/* Allocate memory for a new linkedList struct : */
	LinkedList* newLinkedList = (LinkedList*) malloc(sizeof(LinkedList));

	/* Assign null head and null tail nodes : */
	newLinkedList -> head	= NULL;
	newLinkedList -> tail 	= NULL;
	newLinkedList -> count = 0;

	return newLinkedList;
}


/* DESCRIPTION :    Insert element at start... */
void insertStart(LinkedList* list, void* entry)
{
	/* Create new node : */	
	LinkedListNode* newNd = (LinkedListNode*) malloc(sizeof(LinkedListNode));

	 
	(newNd -> data) = entry;
	(newNd -> next) = NULL;

	
	/* CHECK - if there is already a node, then insert at @ tail + update tail : */
	if (list -> count > 0)
	{		
		newNd -> next = (list -> head);	
		list -> head = newNd;			
	}


	/* CHECK - if no nodes yet, then add 1st node to head & tail : */
	if (list -> count == 0)
	{
		list -> tail = newNd;
		list -> head = newNd;
	}

	/* Increment list size : */
	(list -> count)++;
}



/* DESCRIPTION :    Remove element at start... */
void* removeStart(LinkedList* list)
{
	LinkedListNode* temp = list -> head;
	void* removedData = (list -> head) -> data;


	/* CHECK - if there is more than 1 node, then delete node @ head : */
	if (list -> tail != NULL)
	{		
		list -> head = (list -> head -> next);
	}


	/* CHECK - if no nodes yet, then null tail : */
	if (list -> head == NULL)
	{
		list -> tail = NULL;
	}

	/* Free node's malloc */
	free(temp);

	/* Increment list size : */
	(list -> count)--;


	/* CHECK - is list was empty : */
	if (list -> count < 0)
	{		
		printf("%s", "\nError: LinkedList empty!\n");
		(list -> count) = 0;		
	}

	return removedData;
}



/* DESCRIPTION :    Insert element at end... */
void insertLast(LinkedList* list, void* entry)
{
	/* Create new node : */
	LinkedListNode* newNd = (LinkedListNode*) malloc(sizeof(LinkedListNode));

	newNd -> data = entry;
	newNd -> next = NULL;


	/* CHECK - if there is more than 1 node, then insert at @ tail, then update tail to newNd : */
	if (list -> tail != NULL)
	{
		list -> tail -> next = newNd;
	}
	list -> tail = newNd;


	/* CHECK - if no nodes yet, then add 1st node to head & tail : */
	if (list -> head == NULL)
	{
		list -> head = newNd;
	}

	/* Increment list size : */
	(list -> count)++;
}



/* DESCRIPTION :    Remove element at end.. */
void* removeLast(LinkedList* list)
{
	void* removedData = (list -> tail) -> data;
	LinkedListNode* temp;
	LinkedListNode* currNd;
	LinkedListNode* seclastNd;

	temp = (list -> tail);
	

	
	if (list -> tail != NULL)
	{
		/* CASE1 - if there is only 1 node : */
		if(list -> count == 1)
		{
			list -> head = NULL;
			list -> tail = NULL;			
		}

		/* CASE2 - if there is more than 1 node, then delete node @ tail : */
		if(list -> count > 1)
		{
			/* Get 2nd last node : */
			currNd = list -> head;		
			do
			{			
				seclastNd = currNd;
				currNd = currNd -> next;		
			}
			while( (currNd -> next) != NULL);

			/* Move ref to 2nd last node : */	
			list -> tail = seclastNd;

			/* Null next node of tail to cut link to last node :*/
			list -> tail -> next = NULL;	

		}

		/* Free node's malloc */
		free(temp);
		
	}

	


	/* Increment list size : */
	(list -> count)--;


	/* CHECK -  if list was empty : */
	if (list -> count < 0)
	{		
		printf("%s", "\nError: LinkedList empty!\n");
		(list -> count) = 0;		
	}

	return (void*)removedData;
}



/* DESCRIPTION :    Return Data at index... */
void* getData(LinkedList* list, int index)
{
	LinkedListNode *node = NULL;
	void* theData = NULL;

	/* CHECK - is index within the max node count :*/
	if(index > ((list -> count)-1))
	{
		printf("\nError: Index out of bounds\n");
	}
	else
	{
		node = list -> head;
		while(index != 0) 
		{
			node = node -> next;
			index--;
		}
		theData = node -> data;
	}

	return (void*)(theData);
}




/* DESCRIPTION :    Free all mallocs used... */
void freeLinkedList(LinkedList* list, listFuncFree funcPtr)
{
	LinkedListNode *node = NULL;
	LinkedListNode *nextNode = NULL;

	node = list -> head;

	while(node != NULL) 
	{
		nextNode = node -> next;

		/* Pass freeing of pData to function */
		(*funcPtr)((*node).data);
		free(node);
		node = nextNode;
	}

	free(list);
}

/* DESCRIPTION :    Write all node 2D array to file... */
void writeLinkedList(LinkedList* inList, FILE* outFile, listFuncWrite funcPtr)
{
	LinkedListNode* currNd = inList -> head;

	while (currNd != NULL)
	{
		(*funcPtr)(currNd -> data, outFile);
		currNd = currNd -> next;
	}
}


/* DESCRIPTION :    Show head and tail pointer address... */
void debugLinkedList(LinkedList* inList, char* prefix) 
{
	printf("\n--------------------------------------------------------------\n");
	printf("%s: LL: pHead:%p pTail:%p\n", prefix, (void*)inList -> head, (void*)inList -> tail);
	printf("--------------------------------------------------------------\n");
}


