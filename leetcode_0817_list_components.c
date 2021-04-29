// build with single_list.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "single_list.h"


int numComponents(Node *head, int g[], int n)
{
	int i = 0, len = get_list_length(head); 
	int *map = malloc(sizeof(int)*len);
	int count = 0;

	//malloc failure
	memset(map, 0, sizeof(sizeof(int)*len));
	//while (i < n && g[i]) {
	while (i < n) {
		map[g[i]] = 1;
		i++;
	}

	for (i = 0; i < len; i++) {
		if (map[i] == 1) {
			count ++;
			while (map[i+1] == 1)
				i++;
		}
	}

	free(map);
	return count;
}

int main(int argc, char **argv)
{
    Node *l1, *l2;
	int g[]= {0,3, 1, 4};
	int ret;
 
    l1 = CreateList(11);
	//l2->data = 9;
    ShowList(l1);
	ret = numComponents(l1, g, 4);
	printf("numComponets %d\n", ret);
	free_list(l1);	
}
