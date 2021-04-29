// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


static Node newHead;
Node* splitListToParts(Node *head, int k)
{
	Node *p = head, *next, *h;
	int len = get_list_length(head);
	int m, n, i, j;

	// len <= k
	// 

	m = len / k;
	n = len % k;

	h = p;
	while (p) {
		for (j = 0; j < n; j++) {
			for (i = 0; i < m; i++) {
				p = p->next;
			}
			next = p->next;
			p->next = NULL;
			p = next;
			ShowList(h);
			h = p;
		}
		//
		for (i = 0; i < m-1; i++) {
			p = p->next;
		}
		next = p->next;
		p->next = NULL;
		p = next;
		ShowList(h);
		h = p;
	}
	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(11);
    ShowList(l1);
	ret = splitListToParts(l1, 3);
    ShowList(ret);
	free_list(ret);	
}
