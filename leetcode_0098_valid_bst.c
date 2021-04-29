// build with queue.c and leetcode_binary.c
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "queue.h"

/**
 * BFS: breadth first search
 * DFS: depth first search
 *
 */
/*
 * Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node’s key.
    The right subtree of a node contains only nodes with keys greater than the node’s key.
    Both the left and right subtrees must also be binary search trees.
 *
 */

typedef enum {false = 0, true = 1} bool;

static bool isValidbst(btree_t * tree, int min, int max)
{
	int value;

	if (tree == NULL) {
		return true;; 
	}

	value = tree->data;
	printf("%d %d %d\n", value, min, max);
	if (value > min && value < max && isValidbst(tree->pleft, min, value) && isValidbst(tree->pright, value, max))
		return true;
	else
		return false;
}

bool isValidBST(btree_t * tree)
{

	if (tree == NULL)
		return false;
	// 2<<30 = 0x80000000
	isValidbst(tree, 0x80000000, 0x7fffffff);	
}

static void inOrderQueue(btree_t *tree, Queue *q)
{
	btree_t * root = tree;
	
	if (root == NULL) return;	

	inOrderQueue(root->pleft, q);
	QueuePush(q, root);	
	inOrderQueue(root->pright, q);
}
bool isValidBST2(btree_t * tree, int n)
{
	Queue q;
	qNode *temp;

	if (tree == NULL)
		return false;

	QueueInit(&q);

	inOrderQueue(tree, &q);	
	
	printf("\n");	
	temp = q.head;
	while (temp && temp->next) {
		if (temp->data->data >= temp->next->data->data) {
			return false;
		}
		printf ("%d\t", temp->data->data);
		temp = temp->next;
	}

	return true;
}

int idx = 0;
static void inOrderMap(btree_t *tree, int *map)
{
	btree_t * root = tree;
	
	if (root == NULL) return;	

	inOrderMap(root->pleft, map);
	map[idx++] = root->data;	
	inOrderMap(root->pright, map);
}
bool isValidBST3(btree_t * tree, int n)
{
	int *map;
	bool ret = true;

	if (tree == NULL)
		return false;

	map = malloc(sizeof(int) * n);
	inOrderMap(tree, map);	
	
	printf("\n");	
	for (int i = 0; i < n-1; i ++) {
		if (map[i] >= map[i+1]) {	
			ret = false;
			break;
		}
	}

	free(map);
	return ret;
}

int main ()
{
	btree_t * ret;
	
	/*
	 *             1
	 *            / \
	 *           2   3
	 *          / \ / \
	 *         4  5 6  7 
	 */
	//int pre[]={1,2,4,5,3,6,7};
	//int ino[]={4,2,5,1,6,3,7};
	/*
	 *             4
	 *            / \
	 *           2   6
	 *          / \ / \
	 *         1  3 5  7 
	 */
	int pre[]={4,2,1,3,6,5,7};
	int ino[]={1,2,3,4,5,6,7};
	// pre-order and in-order -> a tree 
	ret = leetcode105_buildPreIn2Tree(pre, ino, 7); 
//	printf ("Inorder: valid %d\n", isValidBST(ret));
//	midOrder_traverse(ret);
	printf ("\nisValidBST2 %d\n", isValidBST2 (ret, 7));
	printf ("\nisValidBST3 %d\n", isValidBST3 (ret, 7));
	return 0;
}
