// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * sortList(Node *list)
{
	Node *cur, *middle, *right, *left;

	if (list == NULL || list->next == NULL)
		return list;

	middle = leetcode876_middleNode(list);
	cur = middle->next;
	middle->next = NULL;
	middle = cur;

	left = sortList(list);
	right = sortList(middle);
	return leetcode21_mergeTwoLinks(left, right);
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(11);
    ShowList(l1);
	ret = sortList(l1);
	ShowList(ret);
	free_list(ret);	
}
