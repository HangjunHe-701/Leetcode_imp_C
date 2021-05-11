// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * deleteDuplicate2(Node *list)
{
	Node head;
	Node *t = list, *prev = NULL, *next; 
	int n;

	head.next = list;

	if (!list || !list->next)
		return list;
	
	while (t && t->next) {
		n = t->data;
		if (n == t->next->data) {
			while (t && n == t->data) {
				next = t->next;
				if (prev == NULL) {
					head.next = next;
				} else {
					prev->next = next;
				}
				free(t);
				t = next;
			}
			continue;
		} 
		prev = t;
		t = t->next;
	}

	return head.next;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(11);
    ShowList(l1);
	ret = deleteDuplicate2(l1);
	ShowList(ret);
	free_list(ret);	
}
