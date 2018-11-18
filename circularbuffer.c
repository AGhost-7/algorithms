/* Circular buffers are good for bounded fifo queues. Thus, the functions
implemented here will focus on this use case. */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <circularbuffer.h>

//#define __CIRCULARBUFFER_DEBUG__

#ifdef __CIRCULARBUFFER_DEBUG__
#include <stdio.h>
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

struct CircularBuffer * circularbuffer_new(size_t size)
{
	struct CircularBuffer * new = malloc(sizeof(struct CircularBuffer));
	void ** items = calloc(size, sizeof(void *));

	new->items = items;
	new->size = size;
	new->read = 0;
	new->write = 0;

	return new;
}

void * circularbuffer_insert(struct CircularBuffer * buffer, void * item)
{
	DEBUG("circularbuffer_insert::current write index: %d\n", buffer->write);

	// The read index should always be behind the write index.
	if (buffer->write == buffer->read) {
		buffer->read++;
		if (buffer->read > buffer->size - 1) buffer->read = 0;
		DEBUG("circularbuffer_insert::new read index: %d\n", buffer->read);
	}

	void * current_item = *(buffer->items + buffer->write);
	*(buffer->items + buffer->write) = item;
	buffer->write++;

	if (buffer->write > buffer->size - 1) buffer->write = 0;
	DEBUG("circularbuffer_insert::new write index: %d\n", buffer->write);

	return current_item;
}

int circularbuffer_insert_clamped(struct CircularBuffer * buffer, void * item)
{
	DEBUG("circularbuffer_insert_clamped::write index: %d\n", buffer->write);
	if (*(buffer->items + buffer->write) != NULL) return -1;
	*(buffer->items + buffer->write) = item;
	buffer->write++;
	if (buffer->write > buffer->size - 1) buffer->write = 0;
	DEBUG("circularbuffer_insert_clamped::new write index: %d\n", buffer->write);
	return 0;
}

void * circularbuffer_remove(struct CircularBuffer * buffer)
{
	void * item = *(buffer->items + buffer->read);

	if (item != NULL) {
		*(buffer->items + buffer->read) = NULL;
		buffer->read++;
	}

	if (buffer->read > buffer->size - 1) buffer->read = 0;

	return item;
}

void circularbuffer_free(struct CircularBuffer * buffer)
{
	// TODO: implement flag
	free(buffer->items);
	free(buffer);
}
