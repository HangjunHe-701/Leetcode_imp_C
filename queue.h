
#ifndef QUEUE_H__
#define QUEUE_H__

typedef struct btree__ {
	int data;
	struct btree__ *pleft;
	struct btree__ *pright;
} btree_t;

typedef  btree_t*  QDataType; 

typedef struct Node {	
	QDataType		data;	
	struct Node*	next;
} qNode; 

// single link with head and tail
typedef struct Queue {	
	struct Node* head;		//front	
	struct Node* tail;		//back
} Queue; 

void QueueInit(Queue* q);
void QueuePush(Queue* q, QDataType data);
void QueuePop(Queue* q);
QDataType QueueFront(Queue* q);
QDataType QueueBack(Queue* q);
int QueueSize(Queue* q);
int QueueEmpty(Queue* q);  
btree_t * leetcode105_buildPreIn2Tree(int* pPreOrder, int* pInOrder, int nodeNum);

btree_t * newTreeNode(int data);
void preOrder_traverse(btree_t * pRoot);
void midOrder_traverse(btree_t * pRoot);
void postOrder_traverse(btree_t * pRoot);
void postOrder_destroy(btree_t * pRoot);
btree_t * deep_copy(btree_t * root);
#endif

