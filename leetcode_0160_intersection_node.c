// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"

/*
 * if a & b have different len, then we will stop the loop after second iteration
 * for the end of first iteration, we just reset the pointer to the head of another linkedlist
 */
// Offer 52 
Node * intersectionNode(Node *head1, Node *head2)
{
	Node *p = head1, *p2 = head2;

	while (p != p2) {
		// no intersection
		if (!p && !p2)	
			return NULL;

		if (p == NULL) {
			p = head2;
		} else
			p = p->next;

		if (p2 == NULL) {
			p2 = head1;
		} else
			p2 = p2->next;
	}
	
	return p;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(11);
    l2 = CreateList(9);
    ShowList(l1);
    ShowList(l2);
	ret = intersectionNode(l1, l2);
	printf("The insertionNode is %d\n", ret? ret->data: -1);
	free_list(l1);	
	free_list(l2);	
}
