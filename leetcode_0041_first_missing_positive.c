// build with rbtree.c for map
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "rbtree.h"
#include "map.h"

int firstMissingPositive(int nums[], int n)
{
	rb_root_t root = RB_ROOT;
	int i, ret;
	
	for (i = 0; i < n; i++) {
		put(&root, nums[i], i);
	}

	// max is n !!!
	for (i = 1; i <= n; i++) {
		if (get(&root, i) == NULL) {
			ret = i;
			goto out;
		}
	}
	ret = n+1; 

out:
	map_destroy(&root);	
	return ret;
}

int main(int argc, char **argv)
{
	int array[] = {3,4,-1,1};
	int ret;
	printf ("The first missing positive is %d\n", firstMissingPositive(array, 4));
}
