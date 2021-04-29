// build with bubble_sort.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

static int ret_index = 0;
static void getCombinationSum(int nums[], int n, int target, int index, int **ret, int *tmp, int tmp_index)
{
	if (target <= 0) {
		if (target == 0) {
			ret[ret_index] = malloc(sizeof(int) * (tmp_index + 1));
			memcpy(ret[ret_index], tmp, sizeof(int) * (tmp_index + 1));
			ret[ret_index][tmp_index] = 0;	
			ret_index ++;
		}
		return;
	}
	
	for (int i = index; i < n; i ++) {
		if (nums[i] > target) {
			break;
		}
		tmp[tmp_index] = nums[i];
		// index not change since the same item can be used infinite times
		getCombinationSum(nums, n, target - nums[i], i, ret, tmp, tmp_index+1);
	}
}

int ** combinationSum(int nums[], int n, int target)
{
	int ** ret;
	int * temp;

	ret = malloc(sizeof(int*) * (1 << n));
	temp = malloc(sizeof(int) *0xff);

	getCombinationSum(nums, n, target, 0, ret, temp, 0);
	free(temp);

	return ret;
}

static void getCombinationSum2(int nums[], int n, int target, int index, int **ret, int *tmp, int tmp_index)
{
	if (target <= 0) {
		if (target == 0) {
			ret[ret_index] = malloc(sizeof(int) * (tmp_index + 1));
			memcpy(ret[ret_index], tmp, sizeof(int) * (tmp_index + 1));
			ret[ret_index][tmp_index] = 0;	
			ret_index ++;
		}
		return;
	}
	
	for (int i = index; i < n; i ++) {
		// ??? key of removing dup. 本次不取重复数字，下次循环可能会取重复数字
		if (i > index && nums[i] == nums[i-1]) { 
			continue;
		}
		if (nums[i] > target) {
			break;
		}
		tmp[tmp_index] = nums[i];
		// index inceased
		getCombinationSum2(nums, n, target - nums[i], i+1, ret, tmp, tmp_index+1);
	}
}

int ** leetcode40_combinationSum(int nums[], int n, int target)
{
	int ** ret;
	int * temp;

	ret = malloc(sizeof(int*) * (1 << n));
	temp = malloc(sizeof(int) *0xff);
    // in order to remove duplicated
	bubble_sort(nums, n);

	getCombinationSum2(nums, n, target, 0, ret, temp, 0);
	free(temp);

	return ret;
}

int main(int argc, char **argv)
{
	int array[] = {2,3,6,7};
	int array2[] = {10,1,2,7,6,1,5};
	int ** ret;

	ret = leetcode40_combinationSum(array2, 7, 8);
	if (ret_index) {
		for (int i = 0; i < ret_index; i ++) {
			int j = 0;
			printf("\n %d:\n", i+1);
			while (ret[i][j]) {
				printf("%d\t", ret[i][j]);
				j ++;
			}
		}
		printf("\n");
		for (int i = 0; i < ret_index; i ++) {
			free(ret[i]);
		}
	}
	free(ret);

	ret_index = 0;
	ret = combinationSum(array, 4, 7);
	if (ret_index) {
		for (int i = 0; i < ret_index; i ++) {
			int j = 0;
			printf("\n %d:\n", i+1);
			while (ret[i][j]) {
				printf("%d\t", ret[i][j]);
				j ++;
			}
		}
		printf("\n");
		for (int i = 0; i < ret_index; i ++) {
			free(ret[i]);
		}
	}
	free(ret);

}
