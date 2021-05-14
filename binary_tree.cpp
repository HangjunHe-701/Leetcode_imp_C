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

//���Ҹ�
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

//���򴴽�һ�ö����� 
btree_t * PreCreateTree()
{
	btree_t * tree;
	int item;

	printf ("Put a number of tree:\n");
	scanf("%d", &item);
	
	if (item == 0) {           //Ҷ�ڵ����ݱ�־����������0 
	    tree = NULL;            //��ĳһ�ڵ�ΪҶ�ӽ�㣬��������������ΪNULL��0��ʾ������
	} else {
		tree = (btree_t*)malloc(sizeof(btree_t));
		if (!tree) {
			return NULL;
		}
		
		tree->data = item;
		tree->pleft = PreCreateTree();             //�ݹ鴴���������� 
		tree->pright = PreCreateTree();            //�ݹ鴴���������� 
	} 
	
	return tree;                              //���ظ��ڵ� 
}

int get_node_num(btree_t * pRoot)
{
	if (pRoot == NULL) // �ݹ����
		return 0;
	
	return get_node_num(pRoot->pleft) + get_node_num(pRoot->pright) + 1;
}

// Offer 55
int get_depth(btree_t * pRoot)
{
	if(pRoot == NULL) // �ݹ����
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
	preOrder_traverse(pRoot->pleft); // ǰ�����������
	preOrder_traverse(pRoot->pright); // ǰ�����������
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
	
	int numLeft = get_nodenum_Kth_Level(pRoot->pleft, k-1); // ��������k-1��Ľڵ����
	int numRight = get_nodenum_Kth_Level(pRoot->pright, k-1); // ��������k-1��Ľڵ����
	return (numLeft + numRight);
}

int get_leafNodeNum(btree_t * pRoot)
{
	if (pRoot == NULL)
		return 0;
	
	if (pRoot->pleft == NULL && pRoot->pright == NULL)
		return 1;
	
	int numLeft = get_leafNodeNum(pRoot->pleft); // ��������Ҷ�ڵ�ĸ���
	int numRight = get_leafNodeNum(pRoot->pright); // ��������Ҷ�ڵ�ĸ���
	return (numLeft + numRight);
}


//�ڶ����������в�����ҹؼ��֣�
void Inserter(btree_t *bt,int key)  
{
	btree_t *parent;   //��ʾ˫�׽�㣻
	btree_t *head = bt;
	btree_t *p=(btree_t *)malloc(sizeof(btree_t));
	p->data=key;   //���������ݣ�
	p->pleft = p->pright = NULL;  //���������ÿգ�
	
	//������Ҫ��ӵĸ���㣬���������Ƕ�Ϊ0�Ľ�㣻
	while(head) 
	{
		parent = head;
		if(key < head->data)   //���ؼ���С�ڽ������ݣ�
			head = head->pleft ; //���������ϲ��ң� 
		else   //���ؼ��ִ��ڽ������ݣ�
			head = head->pright;  //���������ϲ��ң�
	}
	//�ж���ӵ�������������������
	if(key < parent->data)   //С�ڸ���㣻
		parent->pleft = p;    //��ӵ���������
	else    //���ڸ���㣻
		parent->pright = p;   //��ӵ���������
}


bool structure_cmp(btree_t * pRoot)
{
	if (pRoot == NULL)
		return false;
	
	if (pRoot->pleft == NULL && pRoot->pright == NULL)
		return true;
	else if (pRoot->pleft == NULL || pRoot->pright == NULL)
		return false;
	
	bool full_Left = structure_cmp(pRoot->pleft); // ��������Ҷ�ڵ�ĸ���
	bool full_right = structure_cmp(pRoot->pright); // ��������Ҷ�ڵ�ĸ���
	return (full_Left && full_right);
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))  

// Offer 55, �������߲�����1
bool IsAVL(btree_t * pRoot, int & height)
{
	if (pRoot == NULL) {
		height = 0;
		return true;
	}
	
	int heightLeft, heightRight;

	// ������������������AVL�����Ҹ߶�������1��������
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
// �ǵݹ�汾
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


//ɾ����㣻
void Deleteer(btree_t *bt,int key)
{
	btree_t *L,*LL;    //��ɾ�������������еĽ��ʱʹ�ã�
	btree_t *p=bt;
	btree_t *parent = bt;
	int child=0;  //0��ʾ��������1��ʾ��������
	if(!bt)    //���������Ϊ�գ����˳���
		return ;
	
	while(p)  //������������Ч��
	{
		if(p->data==key)
		{
			if(!p->pleft&&!p->pright)  //Ҷ���(����������Ϊ��)��
			{
				if(p==bt)  //��ɾ���Ľ��ֻ�и���㣻
					free(p);
				else if(child==0)
				{
					parent->pleft=NULL;  //���ø����������Ϊ�գ�
					free(p);   //�ͷŽ��ռ䣻
				}
				else   //�����Ϊ��������
				{
					parent->pright=NULL;  //���ø����������Ϊ�գ�
					free(p);  //�ͷŽ��ռ䣻
				}
			}

			else if(!p->pleft)  //������Ϊ�գ���������Ϊ�գ�
			{
				if(child==0)    //�Ǹ�������������
					parent->pleft=p->pright;
				else      //�Ǹ�������������
					parent->pright=p->pright;
				free(p);  //�ͷű�ɾ���Ľ�㣻
			}

			else if(!p->pright)  //������Ϊ�գ���������Ϊ�գ�
			{
				if(child==0)  //�Ǹ�������������
					parent->pleft=p->pleft;
				else      //�Ǹ�������������
					parent->pright=p->pleft;
				free(p);  //�ͷű�ɾ���Ľ�㣻
			}

			else
			{
				LL=p;  //�����������Ľ�㣻
				L=p->pright;  //�ӵ�ǰ�������������в��ң�
				if(L->pleft)  //��������Ϊ�գ�
				{
					LL=L;
					L=L->pleft;   //������������
					p->data=L->data;  //�������������ݱ��浽��ɾ����㣻
					LL->pleft=L->pleft;  //���ø�����������ָ��Ϊ�գ�
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

		else if(key<p->data)  //��ɾ����¼�Ĺؼ���С�ڽ������ݣ�
		{
			//Ҫɾ���Ľ��p��parent����������
			child=0;  //����ڵ�ǰ�����������
			parent=p;//���浱ǰ�����Ϊ����㣻
			p=p->pleft;  //������������
		}

		else  //��ɾ����¼�Ĺؼ��ִ��ڽ������ݣ�
		{
			//Ҫɾ���Ľ��p��parent����������
			child=1;  //����ڵ�ǰ������������ң�
			parent=p;  //���浱ǰ�����Ϊ����㣻
			p=p->pright;  //������������
		}
	}
}

int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
	// maxLeft, �������еĽڵ������ڵ����Զ����
	// maxRight, �������еĽڵ������ڵ����Զ����
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
		if(mustHaveNoChild) // �Ѿ��������п������Ľڵ��ˣ�������ֵı���ΪҶ�ڵ㣨����������Ϊ�գ�
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

