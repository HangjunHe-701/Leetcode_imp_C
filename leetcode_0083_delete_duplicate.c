// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * deleteDuplicate(Node *list)
{
	Node *t = list, *p; 

	if (!list || !list->next)
		return list;
	
	while (t->next) {
		if (t->data == t->next->data) {
			p = t->next;
			t->next = t->next->next;
			free(p);
		} else {
			t = t->next;
		}
	}

	return list;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(29);
    ShowList(l1);
	ret = deleteDuplicate(l1);
	ShowList(ret);
	free_list(ret);	
}
