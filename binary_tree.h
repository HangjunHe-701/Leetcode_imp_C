

#ifndef	BINARY_TREE_H_ 
#define BINARY_TREE_H_

typedef struct btree__ {
	int data;
	struct btree__ *pleft;
	struct btree__ *pright;
} btree_t;

btree_t * leetcode105_buildPreIn2Tree(int* pPreOrder, int* pInOrder, int nodeNum);

btree_t * newTreeNode(int data);
void preOrder_traverse(btree_t * pRoot);
void midOrder_traverse(btree_t * pRoot);
void postOrder_traverse(btree_t * pRoot);
void postOrder_destroy(btree_t * pRoot);
btree_t * deep_copy(btree_t * root);
#endif

