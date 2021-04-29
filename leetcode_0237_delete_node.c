// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


void deleteNode(Node *node)
{
	if  (node == NULL)
		return;

	while (node->next->next) {
		node->data = node->next->data;
		node = node->next;
	}
	// the last node
	node->data = node->next->data;
	free (node->next);
	node->next = NULL;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    ShowList(l1);
	deleteNode(l1->next->next);
    ShowList(l1);
	free_list(l1);	
}
