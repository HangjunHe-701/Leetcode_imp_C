#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <queue.h>


bool leetcode100_isSameTree(btree_t * t1, btree_t * t2)
{
	if (t1 == NULL && t2 == NULL)
		return true;
	if (t1 == NULL || t2 == NULL)
		return false;
	
	return ((t1->data == t2->data) && leetcode100_isSameTree(t1->pleft, t2->pleft) &&
			leetcode100_isSameTree(t1->pright, t2->pright));
}

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

// Offer 27
void offer27_invertTree(btree_t * root)
{
	btree_t *temp;

	if (root == NULL)
		return;
	if (!root->pleft && !root->pright)
		return;
	
    // 交换左子树和右子树
	temp = root->pright;
	root->pright = root->pleft;
	root->pleft = temp;
	
	if (root->pleft)
		offer27_invertTree(root->pleft);
	if (root->pright)
		offer27_invertTree(root->pright);
}

// Offer 28
bool leetcode101_isSymmetric(btree_t *root)
{
	if (!root) return true;

	leetcode226_invertTree(root->pleft);

	return (leetcode100_isSameTree(root->pleft, root->pright));

}

static bool getSymmetric(btree_t * root1, btree_t * root2)
{
	if (!root1 && !root2)
		return true;
	if (!root1 || !root2)
		return false;
	if (root1->data != root2->data)
		return false;

	return (getSymmetric(root1->pleft, root2->pright) &&
			getSymmetric(root1->pright, root2->pleft)) 
}
bool offer28_isSymmetric(btree_t *root)
{
	if (!root) return true;

	retrn getSymmetric(root, root);
}
