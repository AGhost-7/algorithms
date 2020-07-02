// see: https://en.wikipedia.org/wiki/Skip_list
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

struct SkipList {
	int (*compare)(void *, void *);
	struct SkipListNode * nodes;
};

struct SkipListNode {
	void * item;
	struct SkipListNode * right;
	struct SkipListNode * left;
	struct SkipListNode * down;
};

struct SkipList * skiplist_new(int (*compare)(void *, void *));

void skiplist_insert(struct SkipList * list, void * item);
//void skiplist_remove(struct SkipList * list, void * item);

void * skiplist_search(struct SkipList * list, void * item);
#endif
