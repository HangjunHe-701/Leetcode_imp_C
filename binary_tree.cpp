#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "binary_tree.h"

/**
 * BFS: breadth first search
 * DFS: depth first search
 *
 */

//左右根
void postOrder_destroy(btree_t * pRoot)
{
	if (pRoot == NULL)
		return;

	postOrder_destroy(pRoot->pleft); 
	postOrder_destroy(pRoot->pright);
	// free
	delete (pRoot);
}

btree_t * newTreeNode(int data)
{
	btree_t *node = new(btree_t);
	if (!node) {
		return NULL;
	}
	node->data = data;
	node->pleft = NULL;	
	node->pright = NULL;	
	return node;
}

//先序创建一棵二叉树 
btree_t * PreCreateTree()
{
	btree_t * tree;
	int item;

	printf ("Put a number of tree:\n");
	scanf("%d", &item);
	
	if (item == 0) {           //叶节点数据标志：其后根两个0 
	    tree = NULL;            //若某一节点为叶子结点，则其左右子树均为NULL，0表示建空树
	} else {
		tree = (btree_t*)malloc(sizeof(btree_t));
		if (!tree) {
			return NULL;
		}
		
		tree->data = item;
		tree->pleft = PreCreateTree();             //递归创建其左子树 
		tree->pright = PreCreateTree();            //递归创建其右子树 
	} 
	
	return tree;                              //返回根节点 
}

int get_node_num(btree_t * pRoot)
{
	if (pRoot == NULL) // 递归出口
		return 0;
	
	return get_node_num(pRoot->pleft) + get_node_num(pRoot->pright) + 1;
}

// Offer 55
int get_depth(btree_t * pRoot)
{
	if(pRoot == NULL) // 递归出口
		return 0;
	
	int depth_Left = get_depth(pRoot->pleft);
	int depth_Right = get_depth(pRoot->pright);
	return depth_Left > depth_Right ? (depth_Left + 1) : (depth_Right + 1); 
}

// root->left->right 
void preOrder_traverse(btree_t * pRoot)
{
	if (pRoot == NULL) {
		return;
	}

	//Visit(pRoot);
	printf ("%d\t", pRoot->data);
	preOrder_traverse(pRoot->pleft); // 前序遍历左子树
	preOrder_traverse(pRoot->pright); // 前序遍历右子树
}

// leetcode-0094, left->root->right
void midOrder_traverse(btree_t * pRoot)
{
	if (pRoot == NULL)
		return;

	midOrder_traverse(pRoot->pleft); 
	//Visit(pRoot);
	printf ("%d\t", pRoot->data);
	midOrder_traverse(pRoot->pright);
}

// left->right->root
void postOrder_traverse(btree_t * pRoot)
{
	if (pRoot == NULL)
		return;

	postOrder_traverse(pRoot->pleft); 
	postOrder_traverse(pRoot->pright);
	//Visit(pRoot);
	printf ("%d\t", pRoot->data);
}




int get_nodenum_Kth_Level(btree_t * pRoot, int k)
{
	if(pRoot == NULL || k < 1)
		return 0;
	
	if(k == 1)
		return 1;
	
	int numLeft = get_nodenum_Kth_Level(pRoot->pleft, k-1); // 左子树中k-1层的节点个数
	int numRight = get_nodenum_Kth_Level(pRoot->pright, k-1); // 右子树中k-1层的节点个数
	return (numLeft + numRight);
}

int get_leafNodeNum(btree_t * pRoot)
{
	if (pRoot == NULL)
		return 0;
	
	if (pRoot->pleft == NULL && pRoot->pright == NULL)
		return 1;
	
	int numLeft = get_leafNodeNum(pRoot->pleft); // 左子树中叶节点的个数
	int numRight = get_leafNodeNum(pRoot->pright); // 右子树中叶节点的个数
	return (numLeft + numRight);
}


//在二叉排序树中插入查找关键字；
void Inserter(btree_t *bt,int key)  
{
	btree_t *parent;   //表示双亲结点；
	btree_t *head = bt;
	btree_t *p=(btree_t *)malloc(sizeof(btree_t));
	p->data=key;   //保存结点数据；
	p->pleft = p->pright = NULL;  //左右子树置空；
	
	//查找需要添加的父结点，这个父结点是度为0的结点；
	while(head) 
	{
		parent = head;
		if(key < head->data)   //若关键字小于结点的数据；
			head = head->pleft ; //在左子树上查找； 
		else   //若关键字大于结点的数据；
			head = head->pright;  //在右子树上查找；
	}
	//判断添加到左子树还是右子树；
	if(key < parent->data)   //小于父结点；
		parent->pleft = p;    //添加到左子树；
	else    //大于父结点；
		parent->pright = p;   //添加到右子树；
}


bool structure_cmp(btree_t * pRoot)
{
	if (pRoot == NULL)
		return false;
	
	if (pRoot->pleft == NULL && pRoot->pright == NULL)
		return true;
	else if (pRoot->pleft == NULL || pRoot->pright == NULL)
		return false;
	
	bool full_Left = structure_cmp(pRoot->pleft); // 左子树中叶节点的个数
	bool full_right = structure_cmp(pRoot->pright); // 右子树中叶节点的个数
	return (full_Left && full_right);
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))  

// Offer 55, 左右树高不大于1
bool IsAVL(btree_t * pRoot, int & height)
{
	if (pRoot == NULL) {
		height = 0;
		return true;
	}
	
	int heightLeft, heightRight;

	// 左子树和右子树都是AVL，并且高度相差不大于1，返回真
	if (IsAVL(pRoot->pleft, heightLeft) &&
		IsAVL(pRoot->pright, heightRight) &&
		abs(heightLeft - heightRight) <= 1)
	{
		height = MAX(heightLeft, heightRight) + 1;
		return true;
	}
	
	return false;
}

// Pre: root->left->right 
btree_t * deep_copy(btree_t * root)
{
	if (root == NULL) 
		return NULL;

	btree_t* node = NULL;

	node = (btree_t *)malloc(sizeof(btree_t));
	if (!node) assert (0);
	
	node->data = root->data;

	//left tree
	node->pleft = deep_copy(root->pleft); 
	//right tree
	node->pright = deep_copy(root->pright); 

	return node;
}


bool find_node_byval(btree_t * pRoot, int k)
{
	if(pRoot == NULL)
		return false;

	if(pRoot->data == k)
		return true;

	bool found = find_node_byval(pRoot->pleft, k);
	if(!found)
		found = find_node_byval(pRoot->pright, k);

	return found;
}

static bool FindNode(btree_t * pRoot, btree_t * pNode)
{
	if(pRoot == NULL || pNode == NULL)
		return false;

	if(pRoot == pNode)
		return true;

	bool found = FindNode(pRoot->pleft, pNode);
	if(!found)
		found = FindNode(pRoot->pright, pNode);

	return found;
}

btree_t * GetLastCommonParent1(btree_t * pRoot, 
                                     btree_t * pNode1, 
                                     btree_t * pNode2)
{
	if(FindNode(pRoot->pleft, pNode1))
	{
		if(FindNode(pRoot->pright, pNode2))
			return pRoot;
		else
			return GetLastCommonParent1(pRoot->pleft, pNode1, pNode2);
	}
	else
	{
		if(FindNode(pRoot->pleft, pNode2))
			return pRoot;
		else
			return GetLastCommonParent1(pRoot->pright, pNode1, pNode2);
	}
}


#if 0
#if 0
// 非递归版本
static bool GetNodePath(btree_t * pRoot, btree_t * pNode, 
                 list<btree_t *> & path)
{
	if(pRoot == pNode)
	{	
		path.push_back(pRoot);
		return true;
	}
	if(pRoot == NULL)
		return false;
	
	path.push_back(pRoot);
	bool found = false;
	
	found = GetNodePath(pRoot->pleft, pNode, path);
	if(!found)
		found = GetNodePath(pRoot->pright, pNode, path);
	if(!found)
		path.pop_back();
	return found;
}

btree_t * GetLastCommonParent2(btree_t * pRoot, btree_t * pNode1, btree_t * pNode2)
{
	if(pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;
	list<btree_t*> path1;
	bool bResult1 = GetNodePath(pRoot, pNode1, path1);
	list<btree_t*> path2;
	bool bResult2 = GetNodePath(pRoot, pNode2, path2);
	if(!bResult1 || !bResult2) 
		return NULL;
	btree_t * pLast = NULL;
	list<btree_t*>::const_iterator iter1 = path1.begin();
	list<btree_t*>::const_iterator iter2 = path2.begin();
	while(iter1 != path1.end() && iter2 != path2.end())
	{
		if(*iter1 == *iter2)
			pLast = *iter1;
		else
			break;
		iter1++;
		iter2++;
	}
	return pLast;
}
#endif


//删除结点；
void Deleteer(btree_t *bt,int key)
{
	btree_t *L,*LL;    //在删除左右子树都有的结点时使用；
	btree_t *p=bt;
	btree_t *parent = bt;
	int child=0;  //0表示左子树，1表示右子树；
	if(!bt)    //如果排序树为空，则退出；
		return ;
	
	while(p)  //二叉排序树有效；
	{
		if(p->data==key)
		{
			if(!p->pleft&&!p->pright)  //叶结点(左右子树都为空)；
			{
				if(p==bt)  //被删除的结点只有根结点；
					free(p);
				else if(child==0)
				{
					parent->pleft=NULL;  //设置父结点左子树为空；
					free(p);   //释放结点空间；
				}
				else   //父结点为右子树；
				{
					parent->pright=NULL;  //设置父结点右子树为空；
					free(p);  //释放结点空间；
				}
			}

			else if(!p->pleft)  //左子树为空，右子树不为空；
			{
				if(child==0)    //是父结点的左子树；
					parent->pleft=p->pright;
				else      //是父结点的右子树；
					parent->pright=p->pright;
				free(p);  //释放被删除的结点；
			}

			else if(!p->pright)  //右子树为空，左子树不为空；
			{
				if(child==0)  //是父结点的左子树；
					parent->pleft=p->pleft;
				else      //是父结点的右子树；
					parent->pright=p->pleft;
				free(p);  //释放被删除的结点；
			}

			else
			{
				LL=p;  //保存左子树的结点；
				L=p->pright;  //从当前结点的右子树进行查找；
				if(L->pleft)  //左子树不为空；
				{
					LL=L;
					L=L->pleft;   //查找左子树；
					p->data=L->data;  //将左子树的数据保存到被删除结点；
					LL->pleft=L->pleft;  //设置父结点的左子树指针为空；
					for(;L->pleft;L=L->pleft);
					L->pleft=p->pleft;
					p->pleft=NULL;
				}
				else
				{
					p->data=L->data;
					LL->pright=L->pright;
				}
			}
			p=NULL;
		}

		else if(key<p->data)  //需删除记录的关键字小于结点的数据；
		{
			//要删除的结点p是parent的左子树；
			child=0;  //标记在当前结点左子树；
			parent=p;//保存当前结点作为父结点；
			p=p->pleft;  //查找左子树；
		}

		else  //需删除记录的关键字大于结点的数据；
		{
			//要删除的结点p是parent的右子树；
			child=1;  //标记在当前结点右子树查找；
			parent=p;  //保存当前结点作为父结点；
			p=p->pright;  //查找右子树；
		}
	}
}

int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
	// maxLeft, 左子树中的节点距离根节点的最远距离
	// maxRight, 右子树中的节点距离根节点的最远距离
	if(pRoot == NULL)
	{
		maxLeft = 0;
		maxRight = 0;
		return 0;
	}
	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight;
	if(pRoot->m_pLeft != NULL)
	{
		maxDistLeft = GetMaxDistance(pRoot->m_pLeft, maxLL, maxLR);
		maxLeft = max(maxLL, maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;
		maxLeft = 0;
	}
	if(pRoot->m_pRight != NULL)
	{
		maxDistRight = GetMaxDistance(pRoot->m_pRight, maxRL, maxRR);
		maxRight = max(maxRL, maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;
		maxRight = 0;
	}
	return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}

bool IsCompleteBinaryTree(BinaryTreeNode * pRoot)
{
	if(pRoot == NULL)
		return false;
	queue<BinaryTreeNode *> q;
	q.push(pRoot);
	bool mustHaveNoChild = false;
	bool result = true;
	while(!q.empty())
	{
		BinaryTreeNode * pNode = q.front();
		q.pop();
		if(mustHaveNoChild) // 已经出现了有空子树的节点了，后面出现的必须为叶节点（左右子树都为空）
		{
			if(pNode->m_pLeft != NULL || pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
		}
		else
		{
			if(pNode->m_pLeft != NULL && pNode->m_pRight != NULL)
			{
				q.push(pNode->m_pLeft);
				q.push(pNode->m_pRight);
			}
			else if(pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
			{
				mustHaveNoChild = true;
				q.push(pNode->m_pLeft);
			}
			else if(pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
			else
			{
				mustHaveNoChild = true;
			}
		}
	}
	return result;
}
#endif

