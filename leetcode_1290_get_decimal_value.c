// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h" 


int getDecimalValue(Node *head)
{
	int sum = 0;

	if (head->next == NULL) return head->data;

	while (head) {
		sum = sum * 2 + head->data;
		head = head->next;
	}

	return sum;
}

int main(int argc, char **argv)
{
	Node *l = CreateList(8);
	int ret;

	ShowList(l);
	ret = getDecimalValue(l);
	ShowList(l);
	printf ("get Decimal is %d\n", ret);
}
