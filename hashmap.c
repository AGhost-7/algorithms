#include <hashmap.h>

#include <murmur3.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define __HASHMAP_DEBUG__

#ifdef __HASHMAP_DEBUG__
#include <stdio.h>
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

struct Hashmap * hashmap_new()
{
	struct HashmapEntry * entries = calloc(sizeof(struct HashmapEntry), HASHMAP_SIZE);
	struct Hashmap * map = malloc(sizeof(struct Hashmap));

	// TODO: actual seed?
	map->seed = 4;
	map->entries = entries;
	
	return map;
}

uint16_t hashmap_index(uint32_t seed, char key [], int keylen)
{
	uint16_t hash[8];
	MurmurHash3_x64_128(key, keylen, seed, hash);
	DEBUG("hashmap_index::index: %u\n", hash[0]);

	// Since we're only using 16 bits, we're going to drop the rest
	return hash[0];
}

/* strcomp isn't going to work since the string may not be null terminated.
 * Instead we implement our own algorithm that should work over any kind of
 * byte. We already require the length for the hash function.
 */
int hashmap_key_compare(char * key1, int key1len, char * key2, int key2len)
{
	if (key1len != key2len) return 0;
	for (int i = 0; i < key1len; i++) {
		char char1 = *(key1 + i);
		char char2 = *(key2 + i);
		if (char1 != char2) return 0;
	}
	return 1;
}

void * hashmap_get(struct Hashmap * map, char key [], int keylen)
{
	int index = hashmap_index(map->seed, key, keylen);
	struct HashmapEntry * entry = map->entries + index;

	if (entry->key == NULL) {
		DEBUG("hashmap_get::key is null\n");
		return NULL;
	}

	if (hashmap_key_compare(key, keylen, entry->key, entry->key_len)) {
		DEBUG("hashmap_get::value found\n");
		return entry->value;
	}

	if (entry->bucket == NULL) {
		DEBUG("hashmap_get::not found, bucket empty\n");
		return NULL;
	}

	DEBUG("hashmap_get::checking if there is match in bucket\n");
	struct HashmapKeyValue * bucket = entry->bucket;
	for (int i = 0; i < entry->bucket_len; i++) {
		struct HashmapKeyValue * item = bucket + i;
		if (hashmap_key_compare(key, keylen, item->key, item->key_len)) return item->value;
	}

	DEBUG("hashmap_get::no match found in bucket\n");
	return NULL;
}

// zero out memory
void hashmap_init_bucket(struct HashmapKeyValue * bucket, int start, int end)
{
	for (int i = start; i <= end; i++) {
		(bucket + i)->value = NULL;
		(bucket + i)->key = NULL;
		(bucket + i)->key_len = 0;
	}
}

void hashmap_set(struct Hashmap * map, char key [], int keylen, void * value)
{
	DEBUG("hashmap_set::called\n");
	uint32_t index = hashmap_index(map->seed, key, keylen);
	DEBUG("hashmap_set::index: %u\n", index);
	struct HashmapEntry * entry = map->entries + index;

	if (entry->key == NULL || hashmap_key_compare(key, keylen, entry->key, entry->key_len)) {
		entry->key = key;
		entry->key_len = keylen;
		entry->value = value;
	} else {
		// key collision. handle by checking if there is an entry we can use
		if (entry->bucket == NULL) {
			DEBUG("hashmap_set::initializing bucket\n");
			entry->bucket_len = 4;
			entry->bucket = malloc(sizeof(struct HashmapKeyValue) * entry->bucket_len);
			hashmap_init_bucket(entry->bucket, 0, 3);
		}

		for (int i = 0; i < entry->bucket_len; i++) {
			struct HashmapKeyValue * kv = entry->bucket + i;
			if (kv->key == NULL) {
				kv->key = key;
				kv->key_len = keylen;
				kv->value = value;
				return;
			}
		}

		// the bucket is out of space so resize it.
		int new_len = entry->bucket_len * 2;
		struct HashmapKeyValue * new_bucket = realloc(
			entry->bucket, sizeof(struct HashmapKeyValue) * new_len);
		hashmap_init_bucket(new_bucket, entry->bucket_len, new_len - 1);

		(new_bucket + entry->bucket_len)->key = key;
		(new_bucket + entry->bucket_len)->key_len = keylen;
		(new_bucket + entry->bucket_len)->value = value;
		entry->bucket = new_bucket;
		entry->bucket_len = new_len;
	}
}

void hashmap_remove(struct Hashmap * map, char key [], int keylen)
{
	// TODO
}
