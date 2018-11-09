#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <binarysearchtree.h>

// This time around we're searching by age
int compare(void * item1, void * item2)
{
	int num1 = *((int *)item1);
	int num2 = *((int *)item2);
	return num1 - num2;
}

void assert_search(struct BinarySearchTree * tree, int num)
{
	void * result = binarysearchtree_search(tree, &num);
	assert(result != NULL);
	int found = *((int *)result);
	assert(found == num);
}

void insert_num(struct BinarySearchTree * tree, int num)
{
	int * item = malloc(sizeof(int));
	*item = num;
	binarysearchtree_insert(tree, item);
}

int main()
{
	struct BinarySearchTree * tree = binarysearchtree_new(&compare);

	insert_num(tree, 6);
	insert_num(tree, 4);
	insert_num(tree, 3);
	insert_num(tree, 5);
	insert_num(tree, 10);

	assert(*((int *)tree->root->value) == 6);
	assert(*((int *)tree->root->left->value) == 4);

	assert_search(tree, 6);
	assert_search(tree, 4);
	assert_search(tree, 10);
	assert_search(tree, 3);

	return 0;
}
