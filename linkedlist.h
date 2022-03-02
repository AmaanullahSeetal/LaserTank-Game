#ifndef LINKEDLIST_H
#define LINKEDLIST_H

	/* Linkedlist Node : */
	typedef struct LinkedListNode 
	{
		void* data;
		struct LinkedListNode* next;

	} LinkedListNode;
	
	
	/* Linkedlist : */
	typedef struct LinkedList 
	{
		LinkedListNode* head;
		LinkedListNode* tail;
		int count;
	
	} LinkedList;
	
	
	/* Generic Function Pointers : */
	typedef void (*listFuncFree)(void*);
	typedef void (*listFuncWrite)(void*, FILE*);
	
	
	/* Function declarations : */
	LinkedList* createLinkedList();
	void insertStart(LinkedList* inList, void* inData);
	void* removeStart(LinkedList* inList);
	void insertLast(LinkedList* list, void* inData);
	void* removeLast(LinkedList* inList);
	void freeLinkedList(LinkedList* list, listFuncFree funcPtr);
	void writeLinkedList(LinkedList* inList, FILE* outFile, listFuncWrite funcPtr);
	void debugLinkedList(LinkedList* list, char* prefix);
	void* getData(LinkedList* list, int index);

#endif
