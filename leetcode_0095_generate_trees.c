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

typedef enum {false = 0, true = 1} bool;

btree_t * generateBSTree(int start, int end)
{
	btree_t *tree, *left, *right; 
	int i;

	if (start > end) {
		return NULL; 
	}
	for (i = start; i <= end; i++) {
		left = generateBSTree(start, i-1);
		right = generateBSTree(i+1, end);

		btree_t * root = malloc(sizeof(btree_t));
		pRoot->data = i;
		pRoot->pleft = NULL;
		pRoot->pright = NULL;
		for _, l := range left {
			for _, r := range right {
				root := &TreeNode{Val: i, Left: l, Right: r}
				tree = append(tree, root)
			}
		}
	}
	return tree
}

void generate_trees(int n)
{
	if (n == 0) {
		return; 
	}
	generateBSTree(1, n)
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
	int pre[]={1,2,4,5,3,6,7};
	int ino[]={4,2,5,1,6,3,7};
	int post[] = {4,5,2,6,7,3,1};

	// pre-order and in-order -> a tree 
	ret = leetcode105_buildPreIn2Tree(pre, ino, 7); 
	printf ("pre order: \n");
	preOrder_traverse(ret);
	printf ("\npre order end \n");
	postOrder_destroy(ret);

	// post-order and in-order -> a tree 
	ret = leetcode106_buildInPost2Tree(post, ino, 7); 
	printf ("post order: \n");
	postOrder_traverse(ret);
	printf ("\n BFS level:\n");
	leetcode102_levelOrder(ret);
	//printf ("\n DFS level:\n");
	//leetcode102_levelOrder2(ret);
	printf ("\n");
	postOrder_destroy(ret);
	
	return 0;
}
