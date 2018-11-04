
#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdint.h>

// 16 bit, rest are collisions which will be handled by placing into the
// bucket.
#define HASHMAP_SIZE 65536

struct HashmapKeyValue {
	void * value;
	char * key;
	int key_len;
};

struct HashmapEntry {
	void * value;
	char * key;
	int key_len;
	struct HashmapKeyValue * bucket;
	int bucket_len;
};

struct Hashmap {
	// seed for the hash
	uint32_t seed;
	struct HashmapEntry * entries;
};

struct Hashmap * hashmap_new();

void * hashmap_get(struct Hashmap * map, char key [], int keylen);

void hashmap_set(struct Hashmap * map, char key [], int keylen, void * value);

void hasmap_remove(struct Hashmap * map, char key [], int keylen);

#endif
