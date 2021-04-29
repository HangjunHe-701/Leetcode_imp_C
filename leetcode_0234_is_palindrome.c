// build with single_list.c
// similar to leetcode_0143_reorder_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


bool isPalindromeList(Node *head)
{
	Node *p = head, *prev, *middle;

	// divide into two lists 
	middle = middleAndPrevNode (head, &prev);
	prev->next = NULL;	

	// reverse right list
	middle = leetcode206_reverseList(middle);

    ShowList(head);
    ShowList(middle);

	while (p) {
		if  (p->data != middle->data)
			return false;

		p = p->next;
		middle = middle->next;
	}
	
	return true;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    ShowList(l1);
	printf("The palindrome is %d\n", isPalindromeList(l1));
	free_list(l1);	
}
