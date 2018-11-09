#include <stdlib.h>
#include <binarysearchtree.h>

//#define __BINARYSEARCHTREE_DEBUG__

#ifdef __BINARYSEARCHTREE_DEBUG__
#include <stdio.h>
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

struct BinarySearchTreeNode * binarysearchtree_new_node(void * value)
{
	struct BinarySearchTreeNode * node = malloc(sizeof(struct BinarySearchTreeNode));

	node->left = NULL;
	node->right = NULL;
	node->value = value;

	return node;
}

struct BinarySearchTree * binarysearchtree_new(int (*compare)(void *, void*))
{
	struct BinarySearchTree * tree = malloc(sizeof(struct BinarySearchTree));
	tree->compare = compare;
	tree->root = binarysearchtree_new_node(NULL);
	return tree;
}

void * binarysearchtree_search(struct BinarySearchTree * tree, void * item)
{
	struct BinarySearchTreeNode * node = tree->root;

	while (node != NULL && node->value != NULL) {
		int comparison = tree->compare(node->value, item);
		if (comparison > 0) {
			DEBUG("binarysearchtree_search::left\n");
			node = node->left;
		} else if (comparison < 0) {
			DEBUG("binarysearchtree_search::right\n");
			node = node->right;
		} else {
			DEBUG("binarysearchtree_search::return\n");
			return node->value;
		}
	}

	return NULL;
}

void _insert(
		struct BinarySearchTreeNode * node,
		int (*compare)(void *, void *),
		void * item)
{
	DEBUG("_insert::item %d\n", *((int *)item));
	if (node->value == NULL) {
		DEBUG("_insert::node->value == NULL\n");
		node->value = item;
	} else {
		int comparison = compare(node->value, item);
		DEBUG("_insert::comparison: %d\n", comparison);
		if (comparison > 0) {
			DEBUG("_insert::left\n");
			if (node->left == NULL) {
				node->left = binarysearchtree_new_node(item);
			} else {
				_insert(node->left, compare, item);
			}
		} else if (comparison < 0) {
			DEBUG("_insert::right\n");
			if (node->right == NULL) {
				node->right = binarysearchtree_new_node(item);
			} else {
				_insert(node->right, compare, item);
			}
		} else {
			// TODO: should I really be replacing?
			node->value = item;
		}
	}
}

void binarysearchtree_insert(struct BinarySearchTree * tree, void * item)
{
	_insert(tree->root, tree->compare, item);
}

// Writing this differently just to show how to perform inserts using a loop
// instead of recursion.
struct BinarySearchTreeNode * binarysearchtree_insert_node(struct BinarySearchTree * tree, void * item)
{
	struct BinarySearchTreeNode * node = tree->root;

	while (node != NULL) {
		if (node->value == NULL) {
			break;
		} else {
			int comparison = tree->compare(node->value, item);
			if (comparison > 0) {
				if (node->left == NULL) {
					node->left = binarysearchtree_new_node(NULL);
					break;
				} else {
					node = node->left;
				}
			} else if(comparison < 0) {
				if (node->right == NULL) {
					node->right = binarysearchtree_new_node(NULL);
					break;
				} else {
					node = node->right;
				}
			} else {
				break;
			}
		}
	}

	return node;
}
