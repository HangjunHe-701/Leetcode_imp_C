#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int searchInsert(int nums[], int n, int target)
{
	// can't use unsigned !!!
	int low = 0, high = n-1;
	int mid;

	while (low <= high) {
		mid = low + (high-low)/2;

		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] > target) {
			high = mid -1;
		} else {
			low = mid + 1;
		}

	}
	return low;
}

int main(int argc, char **argv)
{
	int array[] = {1,3,5,6};

	int ret = searchInsert(array, 4, 0);
	printf ("return is %d\n", ret);

	ret = searchInsert(array, 4, 7);
	printf ("return is %d\n", ret);
}
