// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"

Node * mergeInBetween(Node *head, int m, int n, Node *head2)
{
	Node *p, *p2, *tmp = head;
	int i;

	for (i = 0; i <= n; i++) {
		if (i == m - 1) {
			p = tmp; 
		}
		if (i == n) {
			p2 = tmp;
		}
		tmp = tmp->next;
	}

	p->next = head2;
	tmp = head2;
	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = p2->next;
	
	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(11);
    l2 = CreateList(6);
    ShowList(l1);
    ShowList(l2);
	ret = mergeInBetween(l1, 1, 1, l2);
    ShowList(ret);
	free_list(ret);	
}
