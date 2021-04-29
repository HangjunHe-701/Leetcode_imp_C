// build with C_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"

Node * reverseBetween(Node *list, int m, int n)
{
	Node *prev = NULL, *t = list, *next, *tail1 = NULL, *tail2 = NULL; 
	int count = 1;

	if (!list || !list->next || m >= n)
		return list;

	while (--m && t->next) {
		tail1 = t;
		t = t->next;
		count ++;
	}
	if (t->next == NULL) return list;

	while (t && count <= n) {
		count ++;
		if (tail2 == NULL) tail2 = t;

		next = t->next;	
		t->next = prev;
		prev = t;
		t = next;
	}

	tail2->next = t; 

	if (tail1) {
		tail1->next = prev;
		return list;
	} 

	return prev;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(10);
    ShowList(l1);
	ret = reverseBetween(l1, 9, 10);
	ShowList(ret);
	free_list(ret);	
}
