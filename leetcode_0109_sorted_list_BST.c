// build with single_list.c
// build with binary_tree.c, queue.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"
#include "queue.h"


btree_t * sortedList2BST(Node *head)
{
	Node *prev = NULL, *middle, *right, *left;
	btree_t *root;

	if (head == NULL)
		return NULL;

	if (head->next == NULL) {
		root = newTreeNode(head->data);
		if (!root) {
			return NULL;
		}
		return root;
	}

	middle = middleAndPrevNode(head, &prev);
	if (middle == NULL)
		return NULL;

	root = newTreeNode(middle->data);
	if (!root) {
		return NULL;
	}
	if (prev)
		prev->next = NULL;
	if (middle == head)
		root->pleft = NULL;
	else
		root->pleft = sortedList2BST(head);
	root->pright = sortedList2BST(middle->next);
	return root;	
}

int main(int argc, char **argv)
{
    Node *l1;
	btree_t *root;
 
    l1 = CreateList(11);
    ShowList(l1);
	root = sortedList2BST(l1);
	midOrder_traverse(root);
	printf("\n");
	free_list(l1);
	postOrder_destroy(root);	
}
