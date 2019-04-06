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
	// No need to use calloc because we set the memory to something valid before
	// reading from it.
	heap->items = malloc(heap->capacity * sizeof(void *));

	return heap;
}

void binaryheap_free(struct BinaryHeap * heap)
{
	free(heap->items);
	free(heap);
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

void * binaryheap_pop(struct BinaryHeap * heap)
{
	if (heap->length == 0) return NULL;

	void * poped = *heap->items;
	DEBUG("pop - poped: %d\n", *((int *) poped));
	// Take the last item and put it at the top, we'll have to re-sort from
	// there.
	*(heap->items) = *(heap->items + heap->length - 1);
	*(heap->items + heap->length - 1) = NULL;

	heap->length--;
	size_t index = 0;
	while (index < heap->length) {
		void * parent = *(heap->items + index);
		void * left = *(heap->items + index * 2 + 1);
		void * right = *(heap->items + index * 2 + 2);

		DEBUG("pop - index: %d, parent: %d, left: %d, right: %d\n",
				index,
				*((int *) parent),
				left == NULL ? -1 : *((int *)left),
				right == NULL ? -1 : *((int *)right));

		if (left != NULL && heap->compare(parent, left) < 0) {
			DEBUG("pop - left\n");
			*(heap->items + index) = left;
			index = index * 2 + 1;
			*(heap->items + index) = parent;
		} else if(right != NULL && heap->compare(parent, right) < 0) {
			DEBUG("pop - right\n");
			*(heap->items + index) = right;
			index = index * 2 + 2;
			*(heap->items + index) = parent;
		} else {
			DEBUG("pop - break\n");
			break;
		}
	}

	// Shrink down the array. Using a different multiple to avoid back and forth
	// resizing.
	if (heap->capacity > heap->length * 3 && heap->capacity > 10) {
		heap->capacity /= 3;
		heap->items = realloc(heap->items, sizeof(void *) * heap->capacity);
	}

	return poped;
}

void * binaryheap_peek(struct BinaryHeap * heap)
{
	return *heap->items;
}
