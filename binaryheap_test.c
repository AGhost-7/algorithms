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

int main()
{
	struct BinaryHeap * heap = binaryheap_new(&record_compare);
	
	for (int index = 0; index < 2; index++) {
		int * item = malloc(sizeof(int));
		*item = index;
		binaryheap_push(heap, item);
	}
	for (int index = 4; index > 0; index--) {
		int * item = malloc(sizeof(int));
		*item = index;
		binaryheap_push(heap, item);
	}
	for (int index = 0; index < heap->length; index++) {
		void * item = heap->items[index];
		printf("item(%d): %d\n", index, *((int *)item));
	}
	void * item = binaryheap_peek(heap);
	printf("peek: %d\n", *((int *)item));

	while (item != NULL) {
		item = binaryheap_pop(heap);
		printf("pop: %d\n", *((int *)item));
	}
}
