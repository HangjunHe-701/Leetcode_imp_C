#include <assert.h>
#include <malloc.h> 
#include "queue.h"


qNode * BuyNode(QDataType data)
{	
	qNode* pNewNode = (qNode *)malloc(sizeof(qNode));	
	if (NULL == pNewNode) {		
		return NULL;	
	} 	

	pNewNode->data = data;	
	pNewNode->next = NULL; 	
	return pNewNode;
} 

void QueueInit(Queue* q)
{
	assert(q);	
	q->head = q->tail = NULL;
} 

void QueuePush(Queue* q, QDataType data)
{	
	assert(q);

	if (q->head == NULL) { 	
		q->head = q->tail = BuyNode(data);	
	} else {		
		q->tail->next = BuyNode(data);		
		q->tail = q->tail->next;	
	}
} 

void QueuePop(Queue* q)
{	
	qNode* pDelNode = q->head;	

	if (pDelNode) {		
		q->head = pDelNode->next;		
		free(pDelNode);
	}
} 

QDataType QueueFront(Queue* q)
{	
	assert(q);	
	return q->head->data;
} 

QDataType QueueBack(Queue* q)
{	
	assert(q);	
	return q->tail->data;
} 

int QueueSize(Queue* q)
{	
	int count = 0;	
	qNode *pCur = q->head;	

	while (pCur)	{		
		++count;		
		pCur = pCur->next;	
	} 	
	return count;
} 

int QueueEmpty(Queue* q)
{	
	return (q->head == NULL);
}
