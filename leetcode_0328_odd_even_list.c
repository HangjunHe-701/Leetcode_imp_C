// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node* oddEvenList(Node *head)
{
	Node *l1, *l2, *p, *head2;

	if (!head || head->next == NULL || head->next->next == NULL)
		return head;

	l1 = head;
	l2 = head->next; 
	head2 = l2;
	p = l2->next;
	while (p && p->next) {
		printf ("%d -> %d\n", p->data, p->next->data);
		l1->next = p;
		l2->next = p->next; 	
		p = p->next->next;
		l1 = l1->next;
		l2 = l2->next;
	}
	// the last node
	if (p) {
		l1->next = p;
		l1 = l1->next;
	}
	l1->next = head2; 
	l2->next = NULL;

	return head;
}

Node* oddEvenList2(Node *head)
{
	Node *odd, *even, *p;
	Node oddHead, evenHead;

	if (!head || head->next == NULL || head->next->next == NULL)
		return head;

	odd = &oddHead;
	even = &evenHead;
	p = head;
	while (p && p->next) {
		odd->next = p;
		even->next = p->next; 	
		p = p->next->next;
		odd = odd->next;
		even = even->next;
	}
	// the last node
	if (p) {
		odd->next = p;
		odd = odd->next;
	}
	odd->next = evenHead.next; 
	even->next = NULL;

	return oddHead.next;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    ShowList(l1);
	ret = oddEvenList2(l1);
    ShowList(ret);
	free_list(ret);	
}
