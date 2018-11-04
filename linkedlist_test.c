#include <stdio.h>
#include "linkedlist.h"

int main() {
	struct LinkedList * list = linkedlist_new();
	printf("size: %u\n", linkedlist_length(list));
	char data [] = "hello world";
	linkedlist_prepend(list, data);
	printf("size: %u\n", linkedlist_length(list));
	linkedlist_prepend(list, "another");
	char * result = list->head;
	printf("first item: %s\n", result);
	result = list->tail->head;
	printf("second item: %s\n", result);
	printf("size: %u\n", linkedlist_length(list));
	result = linkedlist_last(list)->head;
	printf("last: %s\n", result);
	linkedlist_append(list, "append");
	printf("appended %u\n", linkedlist_length(list));
	result = list->tail->tail->head;
	printf("list->tail->tail->head: %s\n", result);
}
