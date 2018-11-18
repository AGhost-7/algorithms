#include <stdlib.h>
#include <stdio.h>
#include <circularbuffer.h>
#include <assert.h>

int main()
{
	struct CircularBuffer * buffer = circularbuffer_new(4);
	char * item;

	assert(circularbuffer_insert(buffer, "one") == NULL);
	assert(circularbuffer_insert(buffer, "two") == NULL);
	assert(circularbuffer_insert(buffer, "three") == NULL);
	assert(circularbuffer_insert(buffer, "four") == NULL);

	item = circularbuffer_remove(buffer);
	assert(item != NULL);
	printf("First item: %s\n", item);

	assert(circularbuffer_insert(buffer, "five") == NULL);

	// the buffer is now full, which means it will start to drop items out.
	printf("inserting\n");
	item = circularbuffer_insert(buffer, "six");
	assert(item != NULL);
	printf("Dropped: %s\n", item);
	item = circularbuffer_remove(buffer);
	printf("Second item: %s\n", item);

	buffer = circularbuffer_new(3);
	assert(circularbuffer_insert_clamped(buffer, "one") == 0);
	assert(circularbuffer_insert_clamped(buffer, "two") == 0);
	assert(circularbuffer_insert_clamped(buffer, "three") == 0);
	assert(circularbuffer_insert_clamped(buffer, "four") == -1);

	printf("First item: %s\n", (char *)circularbuffer_remove(buffer));
	printf("Second item: %s\n", (char *)circularbuffer_remove(buffer));
	printf("Third item: %s\n", (char *)circularbuffer_remove(buffer));
	printf("Fourth item: %s\n", (char *)circularbuffer_remove(buffer));

}
