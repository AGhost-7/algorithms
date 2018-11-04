#include "linkedlist.h"
#include <stdlib.h>
#include <stddef.h>

struct LinkedList * linkedlist_new()
{
	struct LinkedList * list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void linkedlist_prepend(struct LinkedList * list, void * value)
{
	if (list->head == NULL) {
		list->head = value;
	} else {
		struct LinkedList * new_link = malloc(sizeof(struct LinkedList));
		new_link->head = list->head;
		new_link->tail = list->tail;
		list->tail = new_link;
		list->head = value;
	}
}

struct LinkedList * linkedlist_last(struct LinkedList * list)
{
	struct LinkedList * ptr = list;
	while (ptr->head != NULL) {
		if (ptr->tail == NULL) return ptr;
		ptr = ptr->tail;
	}
	return ptr;
}

void linkedlist_append(struct LinkedList * list, void * value) {
	struct LinkedList * end = linkedlist_last(list);
	if (end->head == NULL) {
		end->head = value;
	} else {
		struct LinkedList * new_link = malloc(sizeof(struct LinkedList));
		new_link->head = value;
		new_link->tail = NULL;
		end->tail = new_link;
	}
}

uint32_t linkedlist_length(struct LinkedList * list)
{
	uint32_t length = 0;
	struct LinkedList * ptr = list;
	while (ptr != NULL) {
		if (ptr->head == NULL) return length;
		length++;
		ptr = ptr->tail;
	}

	return length;
}
