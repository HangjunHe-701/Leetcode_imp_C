#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 


static bool searchMatrix(int nums[][4], int m, int n, int target)
{
	int low, high;
	int mid;
	int found_raw = -1;

	// search the first column
	low = 0; high = m - 1;
	while (low <= high) {

		mid = low + (high - low)/2;
		if (nums[mid][0] == target) {
			return true;
		}
		else if (nums[mid][0] > target) {
			high = mid - 1;
		} else {
			if (nums[mid+1][0] > target) {
				found_raw = mid;
				break;
			}
			low = mid + 1;
		}
	}
	
	printf("found %d\n", found_raw);
	if (found_raw == -1) return false;

	low = 0; high = n - 1;
	while (low <= high) {

		mid = low + (high - low)/2;
		if (nums[found_raw][mid] == target) {
			return true;
		}
		else if (nums[found_raw][mid] > target) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	int array[][4] = {{1,3,5,7},{10,11,16,20},{23,30,34,50}};
	int m = 3;
	int n = 4;
	int k = 11;
	printf("search %d in matrix %d\n", k, searchMatrix(array, m, n, k));

	return 0;
}
