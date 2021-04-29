// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * rotateRight(Node *list, int n)
{
	Node *head = NULL, *t = list, *last; 
	int count = 1, k;

	if (!list || !list->next)
		return list;
	
	while (t->next) {
		count++;
		t = t->next;
	}
	// original list
	if (n % count == 0) return list;

	last = t;
	k = count - n % count;	

	t = list;
	while (--k) {
		t = t->next;
	}
	head = t->next;
	t->next = NULL;
	last->next = list;

	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(10);
    ShowList(l1);
	ret = rotateRight(l1, 5);
	ShowList(ret);
	free_list(ret);	
}
