#include <stdio.h>

#include <hashmap.h>

int main() {
	struct Hashmap * map = hashmap_new();
	char * data = "this is a sample";
	printf("setting hashmap\n");
	hashmap_set(map, "data", 4, data);
	printf("now getting\n");
	char * result = (char *)hashmap_get(map, "data", 4);
	printf("result: %s", result);
	return 0;
}
