// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * removeNthFromEnd(Node *list, int n)
{
	Node *prev = NULL, *current, *end;

	if (!list) return NULL;
	
	current = list;
	end = list;
	while (n-- > 0 && end) {
		end = end->next;
	}
	if (n > 0) return NULL;

	while (end) {
		prev = current;
		current = current->next;
		end = end->next;
	}
	// head
	if (!prev) { 
		list = list->next;
		free(current);
	} else {
		prev->next = current->next;
		free(current);
	}

	return list;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(9);
    ShowList(l1);
	ret = removeNthFromEnd(l1, 9);
	ShowList(ret);
	free_list(ret);	
}
