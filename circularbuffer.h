#ifndef _CIRCULARBUFFER_H_
#define _CIRCULARBUFFER_H_

#include <stddef.h>

struct CircularBuffer {
	size_t size;
	int read;
	int write;
	void ** items;
};

struct CircularBuffer * circularbuffer_new(size_t size);

/* Insert an item into the circular buffer. Returns a pointer to the item
which has been replaced by the new item. If the circular buffer isn't full
it will return a null pointer. */
void * circularbuffer_insert(struct CircularBuffer * buffer, void * item);

/* remove the first item in the circular buffer */
void * circularbuffer_remove(struct CircularBuffer * buffer);

#endif
