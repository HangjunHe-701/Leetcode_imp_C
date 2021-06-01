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

// Post Order
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

// Offer 27, Pre Order
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
