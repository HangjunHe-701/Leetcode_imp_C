#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

/*
题目要求输出数组中某个区间内数字之和最大的那个值。
dp[i] 表示 [0,i] 区间内各个子区间和的最大值，状态转移方程是 
dp[i] = nums[i] + dp[i-1] (dp[i-1] > 0)，
dp[i] = nums[i] (dp[i-1] ≤ 0)。
*/

// Offer 42
static int maxSubArray(int nums[], int n)
{
	int *dp;
	int max = nums[0];

	if (n == 1) {
		return nums[0];
	}

	dp = malloc(sizeof(int) * n);
	memset(dp, 0, sizeof(int) * n);

	dp[0] = nums[0];
	for (int i = 1; i < n; i++) {
		if (dp[i-1] > 0) {
			dp[i] = dp[i-1] + nums[i];
		} else {
			dp[i] = nums[i];
		}
		max = MAX(max, dp[i]);
	}

	free(dp);
	return max;	
}

static int maxSubArray2(int nums[], int n)
{
	int max = nums[0];
	int res = 0;

	if (n == 1) {
		return nums[0];
	}

	for (int i = 0; i < n; i++) {
		res += nums[i];

		max = MAX(max, res);
		if (res < 0) {
			res = 0;
		}
	}

	return max;	
}

int main(int argc, char **argv)
{
	int array[] = {-2,1,-3,4,-1,2,1,-5,4};

	printf ("The count of max sub array %d\n", maxSubArray(array, 9));
	printf ("The count of max sub array %d\n", maxSubArray2(array, 9));
}
