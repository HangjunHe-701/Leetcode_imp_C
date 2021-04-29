#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

static int * plusOne(int *nums, int *count)
{
	int i;
	int *ret;

	for (i = *count - 1; i >= 0; i--) {
		nums[i] ++;
		if (nums[i] != 10) {
			return nums;
		}
		nums[i] = 0;
	}

	// all carry
	(*count)++;
	ret = malloc(sizeof(int) * (*count));	
	ret[0] = 1;	
	memcpy(&ret[1], nums, sizeof(int) * (*count - 1));

	return ret;
}

int main(int argc, char **argv)
{
	int array[] = {9,9,9,9};
	int *ret;
	int n = 4;

	ret = plusOne(array, &n);
	printf("Plus one\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t", ret[i]);
	}
	printf("\n");
	if (n != 4)
		free(ret);
	return 0;
}
