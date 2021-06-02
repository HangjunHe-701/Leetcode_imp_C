// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


Node * listPartition(Node *list, int n)
{
	Node *t = list, *nt, *nt2, *head = NULL, *head2 = NULL; 

	if (!list || !list->next)
		return list;
	
	while (t) {
		if (t->data < n) {
			if (head == NULL) {
				head = t;
			} else {
				nt->next = t;
			}
			nt = t;
			//nt->next = NULL;
		} else {
			if (head2 == NULL) {
				head2 = t;
			} else {
				nt2->next = t;
			}
			nt2 = t;
			//nt2->next = NULL;
		}
		t = t->next;
	}

	if (head && !head2) return head;
	if (!head && head2) return head2;
	// the last nodes
	nt->next = head2;
	nt2->next = NULL;

	return head;
}

int main(int argc, char **argv)
{
    Node *l1, *ret;
 
    l1 = CreateList(10);
    ShowList(l1);
	ret = listPartition(l1, 50);
	ShowList(ret);
	free_list(ret);	
}
