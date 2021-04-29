// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"

Node * swapNodes(Node *head, int k)
{
	Node *p = head, *n;
	Node *p2 = head;
	int tmp;

	if (head == NULL || head->next == NULL) {
		return head;
	}

	while (--k) {
		p = p->next;
	}
	n = p;
	while (n->next) {
		p2 = p2->next;
		n = n->next;
	}
	tmp = p->data;
	p->data = p2->data;
	p2->data = tmp;
	
	return head;
}

Node * swapNodes2(Node *head, int k)
{
	int len = get_list_length(head); 
	Node *prev = NULL, *p = head;
	Node *prev2 = NULL, *p2 = head, *n;
	int x = len-k;

	if (len < 2) {
		return head;
	}

	while (--k) {
		prev = p;
		p = p->next;
	}
	while (x--) {
		prev2 = p2;
		p2 = p2->next;
	}
	if (prev == NULL)
		head = p2;
	else
		prev->next = p2;
	prev2->next = p;

	n = p2->next;
	p2->next = p->next;
	p->next = n;

	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(11);
    ShowList(l1);
	ret = swapNodes(l1, 1);
    ShowList(ret);
	free_list(ret);	
}
