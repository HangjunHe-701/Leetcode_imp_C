// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"

Node * swapPairs(Node *list)
{
	Node *head = NULL, *t1, *t2, *prev;

	if (!list || !list->next)
		return list;
	
	while (list && list->next) {
		t1 = list;
		t2 = list->next;	
		t1->next = list->next->next;
		t2->next = t1;

		if (head == NULL) {
			head = t2;
		} else {
			prev->next = t2;	
		}

		prev = t1;
		list = t1->next;
	}
	// the last node
	if (list)
		prev->next = list;
	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *ret, *l2, *ret2;
 
    l2 = CreateList(9);
    l1 = CreateList(6);
    ShowList(l1);
    ShowList(l2);
	ret = swapPairs(l1);
	ret2 = swapPairs(l2);
	ShowList(ret);
	ShowList(ret2);
	free_list(ret);	
	free_list(ret2);	
}
