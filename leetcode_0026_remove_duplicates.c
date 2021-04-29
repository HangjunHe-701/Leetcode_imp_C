#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"


int * removeDuplicates(int* nums, int *n)
{
	int last = 0, index;

	for (index = 1; index < *n; index++) {

		while ((index < *n - 1) && (nums[last] == nums[index])) {
			index++;
		}
		// diff
		last ++;
		nums[last] = nums[index];
	}

	*n = last + 1;

	return nums;
}

int * leetcode27_removeElement(int* nums, int *n, int val)
{
	int last = 0, index;

	// the first item may be removed, index should be from '0'
	for (index = 0; index < *n; index++) {

		while ((index < *n - 1) && (val == nums[index])) {
			index++;
		}
		// diff
		nums[last] = nums[index];
		last ++;
	}

	*n = last;

	return nums;
}

int * leetcode80_removeDuplicates(int* nums, int *n)
{
	int last = 0, index;
	int more;

	for (index = 1; index < *n; index++) {

		more = 0;
		while ((index < *n - 1) && (nums[last] == nums[index])) {
			more++;
			index++;
		}
		// diff, we need keep twise
		if (more) {
			last ++;
			nums[last] = nums[last-1];
		}
		last++;
		nums[last] = nums[index];
	}

	*n = last + 1;

	return nums;
}

int * leetcode283_moveZeros(int* nums, int n)
{
	int last = 0, index;

	for (index = 0; index < n; index++) {

		while ((index < n - 1) && (nums[index] == 0)) {
			index++;
		}
		// not zero 
		nums[last++] = nums[index];
	}

	while (n - last > 0) {
		nums[last++] = 0;
	}
	return nums;
}

int * leetcode283_moveZeros2(int* nums, int n)
{
	int last = 0, index, tmp;

	for (index = 0; index < n; index++) {
		if (nums[index] != 0) {
			if (index != last) {
				// swap
				tmp = nums[index];
				nums[index] = nums[last];
				nums[last] = tmp;
			}
			last ++;
		}
	}

	return nums;
}

int main(int argc, char **argv)
{
    int array[] = {0,0,1,1,1,2,2,3,3,4};
    int n = sizeof(array)/sizeof(int);

    int *ret = removeDuplicates(array, &n);
    printf("num after remove duplicated %d:\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ret[i]);
	}

    int array4[] = {0,0,1,1,1,2,2,3,3,4};
    n = sizeof(array4)/sizeof(int);
    //ret = leetcode283_moveZeros(array4, n);
    ret = leetcode283_moveZeros2(array4, n);
    printf("num after leetcode-283 remove zero %d:\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ret[i]);
	}

    int array3[] = {0,0,1,1,1,2,2,3,3,4};
    n = sizeof(array3)/sizeof(int);
    ret = leetcode80_removeDuplicates(array3, &n);
    printf("num after leetcode-80 remove duplicated %d:\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ret[i]);
	}

    int array2[] = {0,1,2,2,3,0,4,2};
    n = sizeof(array2)/sizeof(int);
	int val = 2;
    ret = leetcode27_removeElement(array2, &n, val);
    printf("num after remove %d: %d:\n", val, n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ret[i]);
	}
}


