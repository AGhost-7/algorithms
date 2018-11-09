/* Binary Search Tree */

#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_

struct BinarySearchTree {
	/* comparison function */
	int (*compare)(void *, void *);
	struct BinarySearchTreeNode * root;
};

struct BinarySearchTreeNode {
	void * value;
	struct BinarySearchTreeNode * left;
	struct BinarySearchTreeNode * right;
};

/* Creates a binary search tree. Requires a comparison function which either
returns -1, 0, or 1 */
struct BinarySearchTree * binarysearchtree_new(int (*compare)(void *, void *));

/* Inserts an item into the binary search tree */
void binarysearchtree_insert(struct BinarySearchTree * tree, void * item);

/* Searches the binary search tree and returns the first match. This is
determined by whenever the compare function returns 0. */
void * binarysearchtree_search(struct BinarySearchTree * tree, void *);

/* Search for where to place item in tree and adds the node if necessary. Returns
the node which is where the item should be inserted into the tree. Does not,
however, insert the item itself into the tree, only the node */
struct BinarySearchTreeNode * binarysearchtree_insert_node(struct BinarySearchTree *, void * item);
#endif
