
#include <stdlib.h>
#include <stdio.h>

typedef enum {false=0, true=1} bool;
typedef struct dnode_ {
	int 		      data;
	struct dnode_    *prev;
	struct dnode_    *next;
} dNode;
typedef dNode* dNodeList;

typedef struct dList_ {
	int 		      size;
	struct dnode_    *head;
	struct dnode_    *tail;
} dList;

#define MAX_HASH  10
#define GET_HASH_IDX  ((x)% MAX_HASH)
typedef struct hash_table__ {
	dList hash[];
} hash_tbl;

int dlist_show(dList *list)
{
	dNode * p = list->head;
	
	while (p) {
		printf ("%d\t", p->data);
		p = p->next;
	}

	p = list->tail;
	while (p) {
		printf ("%d\t", p->data);
		p = p->prev;
	}
	printf ("\n");
	return 0;
}

int dlist_insert_head(dList *list, dNode * element)
{
	if (list->head) {
		element->next = list->head;
		list->head->prev = element;
	}
	
	list->head = element;
	if (!list->tail) list->tail = element;
	
	list->size++;
	return 0;
}

int dlist_insert_tail(dList *list, dNode * element)
{
	if (list->tail) {
		element->prev = list->tail;
		list->tail->next = element;
	}
	list->tail = element;
	if (!list->head) list->head = element;
	
	list->size++;
	return 0;
}

dList * dlist_create(int n)
{
	dNode * p;
	dList * head;
	int i;

	if (n < 1) return NULL;
	
	if ((head = (dList *)malloc(sizeof(dList))) == NULL) return NULL;

	head->size = 0;
	head->head = NULL;
	head->tail = NULL;
	
	for (i = 0; i < n; i++) {
		if ((p = (dNode *)malloc(sizeof(dNode))) == NULL) {
			// free the list
			return NULL;
		}

		p->data = i;
		p->next = NULL;
		p->prev = NULL;
		if (i == 5) p->data =7;
		dlist_ins_tail(head, p);
	}

	return head;
}

/* Insert current node previous position */
int dlist_insert_prev(dList *list, dNode * element, int n)
{
	dNode * p;

	if (!element && list->size != 0) return -1;
	if ((p = (dNode *)malloc(sizeof(dNode))) == NULL) return -1;

	p->data = n;
	// THe first Node
	if (!element->prev) {
		list->head = p;
		p->prev = NULL;
		p->next = element;
		element->prev = p;
	} else {
		element->prev->next = p;
		p->prev = element->prev;
		p->next = element;
		element->prev = p;
	}

	list->size++;
	return 0;

}

/* Insert current node next position */
int dlist_insert_next(dList *list, dNode * element, int n)
{
	dNode * p;

	if (!element && list->size != 0) return -1;
	if ((p = (dNode *)malloc(sizeof(dNode))) == NULL) return -1;

	p->data = n;
	// tail
	if (!element->next) {
		list->tail = p;
		p->prev = element;
		p->next = NULL;
		element->next = p;

	} else {
		element->next->prev = p;
		p->prev = element;
		p->next = element->next;
		element->next = p;
	}

	list->size++;
	return 0;
}


/* Del current node  */
static int dlist_remove_node(dList *list, dNode * element)
{

	if (!element && list->size != 0) return -1;

	// tail
	if (!element->next) {
		list->tail = element->prev;
		element->prev->next = NULL;
	}
	// head
	else if (!element->prev) {
		list->head = element->next;
		element->next->prev = NULL;

	} else {
		element->next->prev = element->prev;
		element->prev->next = element->next;
	}

	list->size--;
	free(element);
	element = NULL;
	return 0;
}


/* Del current node  */
int dlist_remove_val(dList *list, int k)
{
	dNode * p = list->head;
	dNode * q;
	
	if (list->size == 0) return -1;

	while (p) {
		if (p->data == k) {
			q = p->next;
			dlist_remove_node (list, p);
			p = q;
			continue;
		}
		p = p->next;
	}
	return 0;
}


int rotate_dlist(dList* list)
{
	if (list == NULL) {
		return -1;
	}

	if (list->size == 0 && list->size == 1) return 0;

	dNode *n, *r = NULL;
	dNode* p = list->head; 
	list->head = list->tail;
	list->tail = p;
	
	while (p) {	
		n = p->next;
		p->next = r;
		p->prev = n;
		r = p;
		p = n;
	}
	return 0;
}

int main ()
{
	dList * head;

	printf ("creating ...\n");
	head = dlist_create(10);
	dlist_show (head);

	printf ("rotate ...\n");
	rotate_dlist(head);
	dlist_show (head);

	printf ("rm val ...\n");
	dlist_rm_val(head, 7);
	dlist_show (head);
	
	return 0;
}

