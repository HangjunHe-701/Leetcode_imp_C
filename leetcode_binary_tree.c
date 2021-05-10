// build with binary_tree.c, queue.c
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

static btree_t * buildPreIn2TreeDFS(int* pPreOrder, int preStart, int preEnd, int *inPos, int inStart)
{
	int rootIdx;

	if (pPreOrder == NULL)
		return NULL;
	if (preStart > preEnd)
		return NULL;
	
	btree_t * pRoot = malloc(sizeof(btree_t));
	assert(pRoot != NULL);
	// 前序遍历的第一个数据就是根节点数据
	pRoot->data = pPreOrder[preStart];
	pRoot->pleft = NULL;
	pRoot->pright = NULL;
	
	// 查找根节点在中序遍历中的位置，中序遍历中，根节点左边为左子树，右边为右子树
	rootIdx = inPos[pPreOrder[preStart]];
	// 重建左子树
	int nodeNumLeft = rootIdx - inStart;
	pRoot->pleft = buildPreIn2TreeDFS(pPreOrder, preStart+1, preStart+nodeNumLeft, inPos, inStart);

	// 重建右子树
	pRoot->pright = buildPreIn2TreeDFS(pPreOrder, preStart+nodeNumLeft+1, preEnd, inPos, rootIdx + 1);
	return pRoot;
}

btree_t * leetcode105_buildPreIn2Tree(int* pPreOrder, int* pInOrder, int nodeNum)
{
	int i;
	int *inPos;
	int max = 0;
	btree_t *result;

	for (i = 0; i < nodeNum; i++) {
		if (pInOrder[i] > max) {
			max = pInOrder[i];
		}
	}

	inPos = (int *) malloc(sizeof(int) * max);
	memset(inPos, 0, sizeof(int) * max);

	for (i = 0; i < nodeNum; i++) {
		inPos[pInOrder[i]] = i;
	}

	result = buildPreIn2TreeDFS(pPreOrder, 0, nodeNum-1, inPos, 0);
	free(inPos);
	return result;
}


static btree_t * buildInPost2TreeDFS(int* pPostOrder, int postStart, int postEnd, int *inPos, int inStart)
{
	int rootIdx;

	if (pPostOrder == NULL)
		return NULL;
	if (postStart > postEnd)
		return NULL;
	
	btree_t * pRoot = malloc(sizeof(btree_t));
	assert(pRoot != NULL);
	// the last node of postOrder is the root 
	pRoot->data = pPostOrder[postEnd];
	pRoot->pleft = NULL;
	pRoot->pright = NULL;
	
	// 查找根节点在中序遍历中的位置，中序遍历中，根节点左边为左子树，右边为右子树
	rootIdx = inPos[pPostOrder[postEnd]];
	// 重建左子树
	int nodeNumLeft = rootIdx - inStart;
	pRoot->pleft = buildInPost2TreeDFS(pPostOrder, postStart, postStart+nodeNumLeft-1, inPos, inStart);

	// 重建右子树
	pRoot->pright = buildInPost2TreeDFS(pPostOrder, postStart+nodeNumLeft, postEnd-1, inPos, rootIdx + 1);
	return pRoot;
}

btree_t * leetcode106_buildInPost2Tree(int* pPostOrder, int* pInOrder, int nodeNum)
{
	int i;
	int *inPos;
	int max = 0;
	btree_t *result;

	for (i = 0; i < nodeNum; i++) {
		if (pInOrder[i] > max) {
			max = pInOrder[i];
		}
	}

	inPos = (int *) malloc(sizeof(int) * max);
	memset(inPos, 0, sizeof(int) * max);

	for (i = 0; i < nodeNum; i++) {
		inPos[pInOrder[i]] = i;
	}

	result = buildInPost2TreeDFS(pPostOrder, 0, nodeNum-1, inPos, 0);
	free(inPos);
	return result;
}


static btree_t * buildInPost2TreeDFS2(int* pPostStart, int* pPostEnd, int* pInStart, int *pInEnd)
{
	// post end is the root
	btree_t * root = malloc (sizeof(btree_t));
	root->data = *pPostEnd;
	root->pleft = root->pright = NULL;

	if (pPostEnd == pPostStart)
		return root;

	// the index of inOrder
	int * pInOrder = pInStart;
	while (pInOrder <= pInEnd && *pInOrder != *pPostEnd)
		pInOrder++;

	if (pInOrder == pInEnd && *pInOrder != *pPostEnd)
		return NULL; // not found, exception

	int leftLen = pInOrder - pInStart;

	if (leftLen > 0) {
		root->pleft = buildInPost2TreeDFS2(pPostStart, pPostStart+leftLen-1, pInStart, pInOrder-1);
	}
	if (leftLen < pPostEnd-pPostStart) {
		root->pright = buildInPost2TreeDFS2(pPostStart+leftLen, pPostEnd-1, pInOrder+1, pInEnd); 
	}

	return root;
}
btree_t * leetcode106_buildInPost2Tree2(int* pPostOrder, int* pInOrder, int nodeNum)
{
	int i;
	int *inPos;
	int max = 0;
	btree_t *result;

	result = buildInPost2TreeDFS2(pPostOrder, pPostOrder+nodeNum-1, pInOrder, pInOrder+nodeNum-1);
	return result;
}

// BFS
void leetcode102_levelOrder(btree_t * pRoot)
{
	Queue queue;
		
	if (pRoot == NULL)
		return;

	QueueInit(&queue);
	QueuePush(&queue, pRoot);
	
	while (!QueueEmpty(&queue))
	{
		btree_t * pNode = QueueFront(&queue);
		printf ("%d\t", pNode->data);
		QueuePop(&queue);

		if(pNode->pleft!= NULL)
			QueuePush(&queue, pNode->pleft);
		
		if(pNode->pright!= NULL)
			QueuePush(&queue, pNode->pright);
	}
	return;
}

# if 0 //wrong
static void levelOrderDFS(Queue *queue, btree_t *root, int level)
{
	if (root == NULL) return;

	levelOrderDFS(queue, root->pleft, level+1);
	levelOrderDFS(queue, root->pright, level+1);
	if (level == 3)
		QueuePush(queue, root);
}

// DFS
void leetcode102_levelOrder2(btree_t * pRoot)
{
	Queue queue;
	Node * tmp;
		
	if (pRoot == NULL)
		return;

	QueueInit(&queue);
	levelOrderDFS(&queue, pRoot, 0);

	// print
	tmp = queue.head;
	while (tmp) {
		printf("%d\t", tmp->data->data);
		tmp = tmp->next;
	}
		
	return;
}
#endif

bool leetcode100_isSameTree(btree_t * t1, btree_t * t2)
{
	if (t1 == NULL && t2 == NULL)
		return true;
	if (t1 == NULL || t2 == NULL)
		return false;
	
	return ((t1->data == t2->data) && leetcode100_isSameTree(t1->pleft, t2->pleft) &&
			leetcode100_isSameTree(t1->pright, t2->pright));
}

// Inorder
btree_t * leetcode226_invertTree(btree_t * root)
{
	if (root == NULL)
		return NULL;
	
	btree_t * left = leetcode226_invertTree(root->pleft);
	btree_t * right = leetcode226_invertTree(root->pright);
    // 交换左子树和右子树
	root->pleft = right;
	root->pright = left;
	return root;
}

bool leetcode101_isSymmetric(btree_t *root)
{
	if (!root) return true;

	leetcode226_invertTree(root->pleft);

	return (leetcode100_isSameTree(root->pleft, root->pright));

}

#if 1
int main ()
{
	btree_t * ret, *ret2, *ret3, *ret4;
	
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
     /*
	  *             4
	  *            / \
	  *           2   6
	  *          / \ / \
	  *         1  3 5  7 
	 */
	int pre2[]={4,2,1,3,6,5,7};
	int ino2[]={1,2,3,4,5,6,7};

	// pre-order and in-order -> a tree 
	ret = leetcode105_buildPreIn2Tree(pre, ino, 7); 
	printf ("pre order: \n");
	preOrder_traverse(ret);
	printf ("\npre order end \n");
	//postOrder_destroy(ret);

	ret2 = deep_copy(ret);
	printf ("\n");
	printf ("deepcopy isSametree %d\n", leetcode100_isSameTree(ret, ret2));
	printf ("\n");
	postOrder_destroy(ret2);

	// post-order and in-order -> a tree 
	ret3 = leetcode106_buildInPost2Tree(post, ino, 7); 
	printf ("\nbuild in-post preorder: \n");
	preOrder_traverse(ret3);

	// 2nd: post-order and in-order -> a tree 
	ret4 = leetcode106_buildInPost2Tree2(post, ino, 7); 
	printf ("\nbuild in-post preorder 2nd: \n");
	preOrder_traverse(ret4);

	printf ("\n BFS level:\n");
	leetcode102_levelOrder(ret);
	//printf ("\n DFS level:\n");
	//leetcode102_levelOrder2(ret);
	printf ("\n");

	printf ("isSametree %d\n", leetcode100_isSameTree(ret, ret2));
	printf ("\npost order: \n");
	leetcode226_invertTree(ret);
	postOrder_traverse(ret);
	printf ("\nisSametree two rets %d\n", leetcode100_isSameTree(ret, ret2));
	printf ("\nisSymmetric %d\n", leetcode101_isSymmetric(ret));

	postOrder_destroy(ret);
	postOrder_destroy(ret2);
	postOrder_destroy(ret3);
	postOrder_destroy(ret4);
	
	return 0;
}
#endif
