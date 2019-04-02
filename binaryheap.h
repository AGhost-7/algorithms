/* Binary Heap */

#ifndef _BINARYHEAP_H_
#define _BINARYHEAP_H_

#include <stddef.h>

struct BinaryHeap {
	/* since this is a generic algorithm, you need to pass in a comparison
	function. */
	int(*compare)(void *, void *);
	/* array of pointers holding the items */
	void ** items;
	/* number of actual items in the heap */
	size_t length;
	/* maximum number of items that the heap can hold based on the allocated
	memory */
	size_t capacity;
};

/* instantiate a binary heap on the *caugh*... heap. */
struct BinaryHeap * binaryheap_new(int(*compare)(void *, void *));
/* add an item to the heap */
void binaryheap_push(struct BinaryHeap * heap, void * item);
/* returns the min/max of the heap without removing it from the heap. */
void * binaryheap_peek(struct BinaryHeap * heap);
/* returns the min/max of the heap while also removing it from the data
structure. */
void * binaryheap_pop(struct BinaryHeap * heap);
#endif
