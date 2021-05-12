// build with binary_tree.c
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <queue>
#include "binary_tree.h"

using namespace std;

/**
 * BFS: breadth first search
 * DFS: depth first search
 *
 */

static btree_t * buildPreIn2TreeDFS(int* pPreOrder, int preStart, int preEnd, int *inPos, int inStart)
{
	int rootIdx;

	if (pPreOrder == NULL)
		return NULL;
	if (preStart > preEnd)
		return NULL;
	
	btree_t * pRoot = new(btree_t);
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
	
	btree_t * pRoot = new(btree_t);
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

// Offer 07
static btree_t * buildInPost2TreeDFS2(int* pPostStart, int* pPostEnd, int* pInStart, int *pInEnd)
{
	// post end is the root
	btree_t * root = new(btree_t);
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
btree_t * offer07_buildInPost2Tree(int* pPostOrder, int* pInOrder, int nodeNum)
{
	int i;
	int *inPos;
	int max = 0;
	btree_t *result;

	result = buildInPost2TreeDFS2(pPostOrder, pPostOrder+nodeNum-1, pInOrder, pInOrder+nodeNum-1);
	return result;
}

// Offer 33, pre-sequence
bool offer33_isSequenceOfBST(int* pPreOder, int nodeNum)
{
	int i = 1, less;
	bool left = true, right = true;

	if (pPreOder == NULL || nodeNum <= 0)
		return false;

	while (pPreOder[i] < pPreOder[0]) i++;

	less = i-1;
	for (; i < nodeNum; ++i) {
		if (pPreOder[i] < pPreOder[0])
			return false;
	}

	if (less > 0)
		left = offer33_isSequenceOfBST(pPreOder+1, less); 
	if (nodeNum - less - 1 > 0)
		right = offer33_isSequenceOfBST(pPreOder+less+1, nodeNum - less - 1);
	
	return (left && right);
}

// BFS, Offer 32
void leetcode102_levelOrder(btree_t * pRoot)
{
	queue<btree_t*> q1;
		
	if (pRoot == NULL)
		return;

	q1.push(pRoot);
	
	while (!q1.empty())
	{
		btree_t * pNode = q1.front();
		printf ("%d\t", pNode->data);
		q1.pop();

		if (pNode->pleft!= NULL)
			q1.push(pNode->pleft);
		
		if (pNode->pright!= NULL)
			q1.push(pNode->pright);
	}

	return;
}

// Offer 32, print by line 
void offer32_levelOrder(btree_t * pRoot)
{
	queue<btree_t*> q1;
	int toBePrinted = 1;
	int levelCount = 0;
	btree_t * temp;
		
	if (pRoot == NULL)
		return;

	q1.push(pRoot);

	//while (q1.size()) {
	while (!q1.empty()) {
		temp = q1.front();
		printf("%d\t", temp->data);
		
		if (temp->pleft) {
			q1.push(temp->pleft);
			levelCount++;
		}
		if (temp->pright) {
			q1.push(temp->pright);
			levelCount++;
		}

		q1.pop();
		if (--toBePrinted == 0) {
			printf("\n");
			toBePrinted = levelCount;
		}
	}
		
	return;
}

// Offer 36
static void offer36_convertNode(btree_t * pNode, btree_t ** pLastNode)
{
	btree_t *current = pNode;

	if (pNode == NULL) return;

	if (current->pleft)
		offer36_convertNode(current->pleft, pLastNode);

	current->pleft = *pLastNode;
    if (*pLastNode) {	
		(*pLastNode)->pright = current;
	}

	*pLastNode = current;
	if (current->pright)
		offer36_convertNode(current->pright, pLastNode);
	return;
}
btree_t * offer36_convert(btree_t * pRoot)
{
	btree_t *pLastNode = NULL, *p;
	offer36_convertNode(pRoot, &pLastNode);

#if 1
	p = pLastNode;
	while (p) {
		printf("%d\t", p->data);
		p = p->pleft;
	}
	printf("\n");
#endif
	return pLastNode;
}

#if 1
int main ()
{
	btree_t * ret, *ret3, *ret4;
	
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
	ret = leetcode105_buildPreIn2Tree(pre2, ino2, 7); 
	printf ("pre order: \n");
	preOrder_traverse(ret);
	printf ("\npre order end \n");

	// post-order and in-order -> a tree 
	ret3 = leetcode106_buildInPost2Tree(post, ino, 7); 
	printf ("\nbuild in-post preorder: \n");
	preOrder_traverse(ret3);

	// 2nd: post-order and in-order -> a tree 
	ret4 = offer07_buildInPost2Tree(post, ino, 7); 
	printf ("\nbuild in-post preorder 2nd: \n");
	preOrder_traverse(ret4);

	printf ("\n BFS level:\n");
	leetcode102_levelOrder(ret);

	printf ("\n BFS level by line:\n");
	offer32_levelOrder(ret);
	printf ("\n");

	printf ("is pre-sequence of BST %d\n", offer33_isSequenceOfBST(pre2, 7));

	midOrder_traverse(ret);
	printf ("\n");
	offer36_convert(ret);

	//postOrder_destroy(ret);
	postOrder_destroy(ret3);
	postOrder_destroy(ret4);

	return 0;
}
#endif
