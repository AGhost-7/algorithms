#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hashmap.h>

int main() {
	struct Hashmap * map = hashmap_new();
	char str [] = "this is a sample";
	char * value = malloc(sizeof(str));
	char * key = malloc(4);
	strcpy(key, "data");

	strcpy(value, str);

	printf("setting hashmap\n");
	hashmap_set(map, key, 4, value);
	printf("now getting\n");
	char * result = (char *)hashmap_get(map, "data", 4);
	printf("result: %s\n", result);
	hashmap_free(map, HASHMAP_FREE_KEY | HASHMAP_FREE_VALUE);
	return 0;
}
