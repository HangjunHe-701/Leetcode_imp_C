#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

/*
由于数组基本有序，虽然中间有一个“断开点”，还是可以使用二分搜索的算法来实现。
现在数组前面一段是数值比较大的数，后面一段是数值偏小的数。
如果 mid 落在了前一段数值比较大的区间内了，那么一定有 nums[mid] > nums[low]，如果是落在后面一段数值比较小的区间内，nums[mid] ≤ ??? nums[low] 。
如果 mid 落在了后一段数值比较小的区间内了，那么一定有 nums[mid] < nums[high]，如果是落在前面一段数值比较大的区间内，nums[mid] >= ??? nums[high] 。
还有 nums[low] == nums[mid] 和 nums[high] == nums[mid] 的情况，单独处理即可。
最后找到则输出 mid，没有找到则输出 -1 。
*/

int search33(int nums[], int n, int target)
{
	unsigned int low = 0, high = n-1;
	unsigned int mid;

	while (low <= high) {
		mid = low + (high-low)/2;

		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] > nums[low]) { // mid在数值大的一部分区间里
			if (nums[low] <= target && target < nums[mid]) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		} else if (nums[mid] < nums[high]) { // mid在数值小的一部分区间里
			if (nums[mid] < target && target <= nums[high]) {
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		} else {
			if (nums[low] == nums[mid]) {
				low++;
			}
			if (nums[high] == nums[mid]) {
				high--;
			}
		}
	}

	return -1;
}

bool leetcode81_searchRotate(int* nums, int n, int k)
{
	int low = 0, high = n - 1, mid;

	while (high >= low) {
		mid = low + (high-low)/2;

		if (nums[mid] == k)
			return true;
		else if (nums[mid] > nums[low]) {
			if (nums[low] <= k && k < nums[mid])	
				high = mid - 1;
			else 
				low = mid + 1;
		} else if (nums[mid] < nums[high]) {
			if (nums[mid] < k && k <= nums[high])	
				low = mid + 1;
			else 
				high = mid - 1;
		} else {
			if (nums[low] = nums[mid])
				low++;
			if (nums[high] = nums[mid])
				high--;
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	int array[] = {3, 4, 7, 8, 9, 0, 1, 2};
	int n = 7;

	int ret = search33(array, 8, n);
	printf ("%d target index is %d\n", n, ret);

	printf ("%d has %d\n", n, leetcode81_searchRotate(array, 8, 5));
}
