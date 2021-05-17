// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * add_two_numbers(Node *l1, Node *l2)
{
	Node head, *current, *nl;
	int carry = 0, d1, d2;

	if (!l1) return l2;
	else if (!l2) return l1;

	while (l1 || l2) {

		if (l1) d1 = l1->data;
		else d1 = 0;

		if (l2) d2 = l2->data;
		else d2 = 0;

		nl = malloc (sizeof (Node));
		// malloc failure not handle yet
		nl->data = (d1 + d2) % 10 + carry;
		nl->next = NULL;
	
		if (head.next == NULL) {
			head.next = nl;
		} else {
			current->next  = nl;
		}

		carry = (d1 + d2 + carry) / 10;
		current = nl; 

		if (l1) l1 = l1->next;
		if (l2) l2 = l2->next;
	}
	// the last node
	if  (carry) {
		nl = malloc (sizeof (Node));
		// malloc failure not handle yet
		nl->data = carry;
		nl->next = NULL;
		current->next = nl;
	}

	return head.next;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    l2 = CreateList(9);
    ShowList(l1);
    ShowList(l2);
	ret = add_two_numbers(l1, l2);
	ShowList(ret);
	free_list(ret);	
	free_list(l1);	
	free_list(l2);	
}
