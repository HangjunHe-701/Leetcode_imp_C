// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


int getDecimalValue(Node *head)
{
	int sum = 0; 
	Node *p = head;

	while (p) {
		sum = sum*2 + p->data;
		p = p->next;
	}

	return sum;
}

int main(int argc, char **argv)
{
    Node *l1;
	int ret;
 
    l1 = CreateList(6);
    ShowList(l1);
	ret = getDecimalValue(l1);
	printf("getDecimalValue %d\n", ret);
	free_list(l1);	
}
