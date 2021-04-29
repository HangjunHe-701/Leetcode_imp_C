#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

static void generateSubsets(int *nums, int n, int k, int start, int **ret, int* ret_index, int *tmp, int tmp_index)
{
	if (k == tmp_index) {
		// there is one item is empty
		if (tmp_index) {
		   	if (tmp_index <= n - 1) tmp[tmp_index] = tmp[tmp_index-1];
			memcpy(ret[(*ret_index)++], tmp, sizeof(int)*n);
		}
		return;
	}
	// i will at most be n - (k - c.size()) + 1
	for (int i = start; i < n-(k-tmp_index)+1; i++) {
		// add this item
		tmp[tmp_index] = nums[i];
		generateSubsets(nums, n, k, i+1, ret, ret_index, tmp, tmp_index+1);
	}
}

// DFS
static int ** subsets(int *nums, int n)
{
	int **ret;
	int *tmp;
	int ret_index = 0;
	int total = 1 << n;

	ret = malloc(sizeof(int *)*total);
	for (int i = 0; i < total; i++) {
		ret[i] = malloc(sizeof(int)*n);
	}
	tmp = malloc(sizeof(int)*n);

	for (int k = 0; k <= n; k++)
		generateSubsets(nums, n, k, 0, ret, &ret_index, tmp, 0);
	free(tmp);
	return ret;
}

static void generateSubsets3(int *nums, int n, int index, int **ret, int* ret_index, int *tmp, int tmp_index)
{
	if (index == n) {
		// there is one item is empty
		if (tmp_index) {
		   	if (tmp_index <= n - 1) tmp[tmp_index] = tmp[tmp_index-1];
			memcpy(ret[(*ret_index)++], tmp, sizeof(int)*n);
		}
		return;
	}

	// add this item
	tmp[tmp_index] = nums[index];
	generateSubsets3(nums, n, index+1, ret, ret_index, tmp, tmp_index+1);

	// skip this item	
	generateSubsets3(nums, n, index+1, ret, ret_index, tmp, tmp_index);
}

// DFS
static int ** subsets3(int *nums, int n)
{
	int **ret;
	int *tmp;
	int ret_index = 0;
	int total = 1 << n;

	ret = malloc(sizeof(int *)*total);
	for (int i = 0; i < total; i++) {
		ret[i] = malloc(sizeof(int)*n);
	}
	tmp = malloc(sizeof(int)*n);

	generateSubsets3(nums, n, 0, ret, &ret_index, tmp, 0);
	free(tmp);
	return ret;
}

// 解法三：位运算的方法
int ** subsets2(int *nums, int n)
{
	int total, i, j, k;
	int **ret;

	if (n == 0) {
		return NULL; 
	}
	total = 1 << n;
	ret = malloc(sizeof(int *)*total);
	for (i = 0; i < total; i++) {
		ret[i] = malloc(sizeof(int)*n);
	}

	for (i = 0; i < total; i++) { // i 从 000...000 到 111...111, 0 means nothing
		int tmp = i;
		k = 0;	
		for (j = n - 1; j >= 0; j--) { // 遍历 i 的每一位
			if (tmp & 1 == 1) {
				ret[i][k++] = nums[j]; 
			}
			tmp >>= 1;
		}
		if (k <= n - 1) ret[i][k] = ret[i][k-1];
	}
	return ret;
}

static void leetcode90_generateSubsets(int *nums, int n, int k, int start, int **ret, int* ret_index, int *tmp, int tmp_index)
{
	if (k == tmp_index) {
		// 0 is invalid 
		memcpy(ret[(*ret_index)++], tmp, sizeof(int)*n);
		return;
	}

	// i will at most be n - (k - c.size()) + 1
	for (int i = start; i < n-(k-tmp_index)+1; i++) {
		// 这里是去重的关键逻辑,本次不取重复数字，下次循环可能会取重复数字 
		// the key of removing duplicated items
		if (i > start && nums[i] == nums[i-1])
			continue;
	
		// add this item
		tmp[tmp_index] = nums[i];
		leetcode90_generateSubsets(nums, n, k, i+1, ret, ret_index, tmp, tmp_index+1);
	}
}

// DFS
static int ** leetcode90_subsets(int *nums, int n, int *ret_index)
{
	int **ret;
	int *tmp;
	int total = 1 << n;

	ret = malloc(sizeof(int *)*total);
	for (int i = 0; i < total; i++) {
		ret[i] = malloc(sizeof(int)*n);
	}
	tmp = malloc(sizeof(int)*n);

	for (int k = 0; k <= n; k++)
		leetcode90_generateSubsets(nums, n, k, 0, ret, ret_index, tmp, 0);
	free(tmp);
	return ret;
}

int main(int argc, char **argv)
{
	int array[] = {1, 2, 3};
	int array2[] = {1, 2, 2};
	int **ret;
	int i,j, n = 3;
	int total = 1 << n;

#if 1
	ret = subsets(array, n);
	printf("subset:\n");
	// the first one is empty
	for (i = 0; i < total; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", ret[i][j]);
			if (j < n -1 && ret[i][j] == ret[i][j+1])
				break;
		}
		printf("\n");
	}
	for (i = 1; i < total; i++) {
		free(ret[i]);
	}
	free(ret);
#endif
#if 1
	ret = subsets2(array, n);
	printf("bitops:\n");
	// the first one is empty
	for (i = 1; i < total; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", ret[i][j]);
			if (j < n -1 && ret[i][j] == ret[i][j+1])
				break;
		}
		printf("\n");
	}
	for (i = 1; i < total; i++) {
		free(ret[i]);
	}
	free(ret);
#endif

	// recursive
	printf("recursive:\n");
	ret = subsets3(array, n);
#if 1
	// the last one is empty
	for (i = 0; i < total-1; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", ret[i][j]);
			if (j < n -1 && ret[i][j] == ret[i][j+1])
				break;
		}
		printf("\n");
	}
	for (i = 1; i < total; i++) {
		free(ret[i]);
	}
	free(ret);
#endif

	// leetcode-90 recursive
	total = 0;
	ret = leetcode90_subsets(array2, n, &total);
	printf("leetcode-90:\n");
#if 1
	// the last one is empty
	for (i = 0; i < total; i++) {
		for (j = 0; j < n; j++) {
			if (ret[i][j])
				printf("%d\t", ret[i][j]);
		}
		printf("\n");
	}
	for (i = 1; i < total; i++) {
		free(ret[i]);
	}
	free(ret);
#endif
	return 0;
}
