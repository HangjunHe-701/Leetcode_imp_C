#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int search34(int nums[], int n, int target, int *start, int *end)
{
	unsigned int low = 0, high = n-1;
	unsigned int mid;
	*start = -1;
	*end = -1;

	while (low <= high) {
		mid = low + (high-low)/2;

		if (nums[mid] == target) {
			if (mid == 0 || nums[mid - 1] != target) {
				*start = mid;
				while (nums[mid+1] == target)
					mid++;

				if (mid != *start) {
					*end = mid;
					return 0;
				} else {
					*start = -1;
					*end = -1;
					return -1;
				}
			}
			high = mid - 1;
		} else if (nums[mid] > target) {
			high = mid -1;
		} else {
			low = mid + 1;
		}

	}
	return -1;
}

int main(int argc, char **argv)
{
	int array[] = {5,7,7,7,7,8,8,9,10};
	int first, last;

	int ret = search34(array, 9, 9, &first, &last);
	printf ("return is %d: [%d, %d]\n", ret, first, last);
}
