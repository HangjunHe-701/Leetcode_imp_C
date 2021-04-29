// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * mergeTwoLinks(Node *l1, Node *l2)
{
	Node *nl, *current;

	if (!l1) return l2;
	if (!l2) return l1;

	// head
	if (l1->data > l2->data) {
		nl = l2;
		l2 = l2->next;
	} else {
		nl =l1;
		l1 = l1->next;
	}

	current = nl;
	while (l1 && l2) {
		if (l1->data > l2->data) {
			current->next = l2;
			l2 = l2->next;
		} else {
			current->next =l1;
			l1 = l1->next;
		}
		current = current->next;
	}

	// tail 
	if (l1) current->next = l1;
	else current->next = l2;	
	
	return nl;
}

// recursion version
Node * mergeTwoLinks2(Node *l1, Node *l2)
{
	if (!l1) return l2;
	if (!l2) return l1;

	if (l1->data > l2->data) {
		l2->next = mergeTwoLinks2(l1, l2->next);
		return l2;
	} else {
		l1->next = mergeTwoLinks2(l1->next, l2);
		return l1;
	}
}

int main(int argc, char **argv)
{
    Node *l1, *ret, *l2;
 
    l2 = CreateList(9);
    l1 = CreateList(6);
    ShowList(l1);
    ShowList(l2);
	ret = leetcode21_mergeTwoLinks(l1, l2);
	ShowList(ret);
	free_list(ret);	
	//ret = mergeTwoLinks2(l1, l2);
	//ShowList(ret);
	//free_list(ret);	
}
