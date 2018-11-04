#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdint.h>

struct LinkedList {
	void * head;
	struct LinkedList * tail;
};

/* Returns an empty linked list with the memory zeroed out. */
struct LinkedList * linkedlist_new();

/* Returns the last node in the linked list */
struct LinkedList * linkedlist_last(struct LinkedList * list);

/* Inserts at the begining of the list */
void linkedlist_prepend(struct LinkedList * list, void * value);

/* Inserts at the end of the list */
void linkedlist_append(struct LinkedList * list, void * value);

/* Returns the number of items in the list */
uint32_t linkedlist_length(struct LinkedList * list);
#endif
