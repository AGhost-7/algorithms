#include <skiplist.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/* These tests cases are inspired from full text search algorithms. A reverse
index is implemented using the skiplist. */

struct TokenMatch {
	char * token;
	struct DocumentTokens ** documents;
};

struct SearchTerm {
	char * token;
};

struct DocumentTokens {
	int id;
	// would contain the number of instances that a single term appears in
	// the document
};

struct Document {
	int id;
	char * text;
};

int compare_token(void * item1, void * item2) {
	return strcmp(item1, item2);
}

void token_test() {
	//struct SkipList * list = skiplist_new(&compare_token);
	//list->nodes = malloc(sizeof(struct SkipListNode));

	//struct TokenMatch token_a = struct TokenMatch {
	//	.token = "a",
	//	.documents = NULL
	//};

	//struct TokenMatch token_b = TokenMatch {
	//	.token = "b",
	//	.documents = NULL
	//};

	//struct TokenMatch token_c = TokenMatch {
	//	.token = "c",
	//	.documents = NULL
	//};

	//list->nodes->item = &token_a;

	//char * search_token = "c";
	//void * result = skiplist_search(list, &search_token);
}

int compare_integer(void * item1, void * item2) {
	int * value1 = (int *) item1;
	int * value2 = (int *) item2;
	return (*value1) - (*value2);
}

void integer_test() {
	struct SkipList * list = skiplist_new(&compare_integer);
	int items [] = {1, 3, 2, 5, 7, 6, 4};
	size_t len = sizeof(items) / sizeof(items[0]);
	for (int i = 0; i < len; i++) {
		printf("items[%d]: %d\n", i, items[i]);
		skiplist_insert(list, &items[i]);
	}

	int search = 3;
	int * result = (int *) skiplist_search(list, &search);
	printf("result: %d", *result);
}

int main() {
	integer_test();
	return 0;
}
