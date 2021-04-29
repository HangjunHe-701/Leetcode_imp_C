// build with single_list.c
// similar to leetcode234_is_palindrome.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * reorderList(Node *list)
{
	Node *prev, *middle, *right, *left;
	Node *p;

	if (list == NULL || list->next == NULL)
		return list;

	middle = middleAndPrevNode(list, &prev);
	prev->next = NULL;

	right = leetcode206_reverseList(middle);
	left = list;

    ShowList(left);
    ShowList(right);
	p = list;
	left = left->next;
	while (right && left) {
		p->next = right;
		right = right->next;

		p->next->next = left;
		left = left->next;

		p = p->next->next;
	}
	// not even
	if (right) {
		p->next = right;
	}

	return list;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(12);
    ShowList(l1);
	ret = reorderList(l1);
	ShowList(ret);
	free_list(ret);	
}
