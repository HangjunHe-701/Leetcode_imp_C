// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * insertionSortList(Node *list)
{
	Node *prev, head, *next, *p;

	if (list == NULL || list->next == NULL)
		return list;

	// extra head is very useful
	head.next = NULL;

	while (list) {
		next = list->next;	
		prev = &head;
		while (prev->next && prev->next->data < list->data) {
			prev = prev->next; 
		}

		list->next = prev->next;
		prev->next = list;
		list = next;
	}
	
	return head.next;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(11);
    ShowList(l1);
	ret = insertionSortList(l1);
	ShowList(ret);
	free_list(ret);	
}
