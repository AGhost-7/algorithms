#include <skiplist.h>
#include <stdlib.h>

#define __SKIPLIST_DEBUG__

#ifdef __SKIPLIST_DEBUG__
#include <stdio.h>
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

struct SkipList * skiplist_new(int (*compare)(void *, void *))
{
	struct SkipList * list = malloc(sizeof(struct SkipList));
	list->compare = compare;
	list->nodes = NULL;
	return list;
}

void * skiplist_search(struct SkipList * list, void * item)
{
	if (list->nodes == NULL) return NULL;

	struct SkipListNode * node = list->nodes;

	while (node != NULL) {
		int comparison = list->compare(node->item, item);
		if (comparison == 0) {
			return node->item;
		} else if (comparison > 0) {
			// if the current node is greater, move to the right
			node = node->right;
		} else {
			// node in the list is less than the provided value, backtrack and move
			// down a level
			node = node->left;
			if (node == NULL) return NULL;
			node = node->down;
		}
	}

	return NULL;
}

int should_level(int depth) {
}

void skiplist_insert(struct SkipList * list, void * item)
{
	struct SkipListNode * node = list->nodes;
	if (node == NULL) {
		list->nodes = malloc(sizeof(struct SkipListNode));
		list->nodes->item = item;
		list->nodes->right = NULL;
		list->nodes->down = NULL;
		list->nodes->left = NULL;
		return;
	}

	while (1) {
		int comparison = list->compare(node->item, item);
		DEBUG("walk node->item: %d", *((int *)node->item));
		if (comparison > 0) {
			// if the current node is greater, then we should move right
			node = node->right;
		} else {
			// if the current node is less, then we should move down
			node = node->left;
		}
	}
}
// 
