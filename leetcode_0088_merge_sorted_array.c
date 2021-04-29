#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

/*

*/
int mergeSortedArray(int *ma, int m, int *na, int n)
{
	int i = m - 1, j = n - 1;
	int k = m + n - 1;

	while (i >= 0 && j >= 0) {
		if (ma[i] > na[j]) {
			ma[k] = ma[i];
			i --;
		} else {
			ma[k] = na[j];
			j --;
		}
		k --;
	}	

	while (j >= 0) {
		ma[k--] = na[j--];
	}
}

int main(int argc, char **argv)
{
	int array[] = {1,2,3,0,0,0};
	int array2[] = {2,5,6};
	int m = sizeof(array)/sizeof(int);
	int n = sizeof(array2)/sizeof(int);

	printf ("largest rectangle area %d\n", mergeSortedArray(array, 3, array2, n));
	for (int i = 0; i < m; i ++) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}
