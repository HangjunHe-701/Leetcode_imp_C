// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


// DFS: recursive, p1 longer than p2
static Node* addNode(Node *p1, Node *p2, int offset)
{
	Node *p, *next;

	if (p1 == NULL)
		return NULL;

	p = malloc(sizeof(Node));
	//failed
	if (offset == 0) {
		next = addNode(p1->next, p2->next, 0);
		p->data = p1->data + p2->data;
	} else {
		next = addNode(p1->next, p2, offset-1);
		p->data = p1->data;
	}

	if (next && next->data > 9) {		
		p->data += 1;
		next->data %= 10;
	}
	p->next = next;

	return p;
}

static Node newHead; // Need be global variable, or will return local variable address
Node* addTwoNumbers(Node *head1, Node *head2)
{
	Node *p;
	int len1, len2, offset = 0;

	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;

	len1 = get_list_length(head1);
	len2 = get_list_length(head2);

	if (len1 > len2) {
		newHead.next = addNode(head1, head2, len1-len2);
	} else {
		newHead.next = addNode(head2, head1, len2-len1);
	}

	if (newHead.next->data > 9) {
		newHead.next->data %= 10;
		newHead.data = 1;
		return &newHead;
	}
	return newHead.next;
}

int main(int argc, char **argv)
{
    Node *l1, *l2, *ret;
 
    l1 = CreateList(9);
    l2 = CreateList(6);
    ShowList(l1);
    ShowList(l2);

	ret = addTwoNumbers(l1, l2);
    ShowList(ret);

	free_list(ret);	
	free_list(l1);	
	free_list(l2);	
}
