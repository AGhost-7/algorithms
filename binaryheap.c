#include <stdlib.h>
#include <assert.h>
#include "binaryheap.h"

//#define __BINARYHEAP_DEBUG__

#ifdef __BINARYHEAP_DEBUG__
#include <stdio.h>
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

struct BinaryHeap * binaryheap_new(int (*compare)(void*, void*))
{
	struct BinaryHeap * heap = malloc(sizeof(struct BinaryHeap));
	heap->length = 0;
	heap->capacity = 10;
	heap->compare = compare;
	heap->items = calloc(heap->capacity, sizeof(void *));

	return heap;
}

void binaryheap_push(struct BinaryHeap * heap, void * item)
{

	if (heap->capacity == heap->length) {
		heap->capacity *= 2;
		heap->items = realloc(heap->items, sizeof(void *) * heap->capacity);
		// We'll have to panic when we run out of memory since this API doesn't
		// really expose any error handling of this sort.
		assert(heap->items != NULL);
	}

	// start at the "bottom" of the tree and work our way up as needed.
	size_t index = heap->length;
	DEBUG("push - pushing(%d): %d\n", index, *((int *)item));

	*(heap->items + index) = item;

	while (index != 0) {
		int parent_index = index / 2;
		void * child_item = *(heap->items + index);
		void * parent_item = *(heap->items + parent_index);
		int comparison = heap->compare(parent_item, child_item);
		DEBUG("push - child(%d): %d, parent(%d): %d, comparison: %d\n",
				index,
				*((int *)child_item),
				parent_index,
				*((int *)parent_item),
				comparison);
		if (comparison < 0) {
			DEBUG("push - switching\n");
			// the parent is lesser than the child, so switch them around
			*(heap->items + index) = parent_item;
			*(heap->items + parent_index) = child_item;
			index = parent_index;
		} else {
			DEBUG("push - breaking\n");
			break;
		}
	}

	heap->length++;
}

void * binaryheap_peek(struct BinaryHeap * heap)
{
	return *heap->items;
}
