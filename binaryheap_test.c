#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "binaryheap.h"

int record_compare(void * parent, void * child)
{
	int num1 = *((int *)parent);
	int num2 = *((int *)child);
	return num1 - num2;
}
void print_heap(struct BinaryHeap * heap)
{
	for (int index = 0; index < heap->length; index++) {
		int * item = (int *)heap->items[index];
		printf("items[%d]: %d\n", index, *item);
	}
}

int main()
{
	struct BinaryHeap * heap = binaryheap_new(&record_compare);
	
	for (int index = 0; index < 2; index++) {
		int * item = malloc(sizeof(int));
		*item = index;
		binaryheap_push(heap, item);
	}
	for (int index = 4; index >= 0; index--) {
		int * item = malloc(sizeof(int));
		*item = index;
		binaryheap_push(heap, item);
	}
	printf("pop start\n");
	int result [] = {4, 3, 2, 1, 1, 0, 0};
	int length = 7;
	for (int index = 0; index < length; index++) {
		int compare = result[index];
		print_heap(heap);
		int value = *((int *) binaryheap_pop(heap));
		printf("index: %d, compare: %d, value: %d\n", index, compare, value);
		assert(value == compare);
	}
}
