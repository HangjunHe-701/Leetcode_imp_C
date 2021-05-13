#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

typedef struct {
	int start;
	int end;
} interval;

// make the last pair sorted first, and recur ahead and left pairs
static int partitionSort(interval * nums, int low, int high) 
{
	interval temp;
	int j = low;

	// max high - 1
	for (int i = low; i < high - 1; i++) {

		// compare with the last node
		if  (nums[i].start < nums[high].start || (nums[i].start == nums[high].start && nums[i].end < nums[high].end)) {
			memcpy(&temp, &nums[i], sizeof(interval));
			memcpy(&nums[i], &nums[j], sizeof(interval));
			memcpy(&nums[j], &temp, sizeof(interval));
			j++;
		}
	}

	memcpy(&temp, &nums[j+1], sizeof(interval));
	memcpy(&nums[high], &nums[j+1], sizeof(interval));
	memcpy(&nums[j+1], &temp, sizeof(interval));
	return j+1;
}

static void quickSort(interval * nums, int low, int high) 
{
	if (high <= low)
		return;

	int p = partitionSort(nums, low, high);
	// smaller than P
	quickSort(nums, low, p-1);
	// bigger than P
	quickSort(nums, p+1, high);
}

static interval * mergeIntervals(interval *nums, int n, int *ret_num)
{
	interval *ret = malloc(sizeof(interval) * n);
	int i;
	int count = 0;
	
	if (n == 0) {
		return NULL;
	}

	// sort the intervals
	quickSort(nums, 0, n-1);
	memcpy(&ret[count++], &nums[0], sizeof(interval));		

	for (i = 1; i < n; i++) {
		if (nums[i].start <= ret[count - 1].end) {
			// merge, end is the maximal of two ends, [1, 8] and [2, 6]
			ret[count - 1].end == MAX(nums[i].end, ret[count-1].end);
		}
		else {
			memcpy(&ret[count++], &nums[i], sizeof(interval));		
		}
	}

	*ret_num = count;
	return ret;
}

/*
可以分 3 段处理，
先添加原来的区间，即在给的 newInterval 之前的区间。
然后添加 newInterval ，注意这里可能需要合并多个区间。
最后把原来剩下的部分添加到最终结果中即可。
*/

static interval * insertIntervals(interval *nums, int n, int *ret_num, interval * insert)
{
	interval *ret = malloc(sizeof(interval) * n + 1);
	int i;
	int count = 0;
	
	if (n == 0) {
		memcpy(&ret[count++], insert, sizeof(interval));		
		return NULL;
	}

	// first step
	for (i = 0; i < n; i++) {
		if (nums[i].end < insert->start) {
			memcpy(&ret[count++], &nums[i], sizeof(interval));		
		} else {
			break;
		}
	}

	// second step
	for (; i < n; i++) {
		if (nums[i].start <= insert->end) {
			insert->end = MAX(insert->end, nums[i].end);	
			insert->start = MIN(insert->start, nums[i].start);	
		} else {
			break;
		}
	}
	memcpy(&ret[count++], insert, sizeof(interval));

	// third step
	for (; i < n; i++) {
		memcpy(&ret[count++], &nums[i], sizeof(interval));
	}

	*ret_num = count;
	return ret;
}

int main(int argc, char **argv)
{
	interval array[] = {{1,3},{2,6},{8,10},{15,18}};
	interval array2[] = {{1,3},{2,6},{8,10},{15,18}};
	interval insert = {12, 23};
	interval *ret;
	int ret_num = 0;
	
	ret = mergeIntervals(array, 4, &ret_num);
	if (ret_num) {
		for (int i = 0; i < ret_num; i++) {
			printf("[%d,%d]\t", ret[i].start, ret[i].end);
		}
		printf("\n");

		free(ret);
	}

	ret = insertIntervals(array2, 4, &ret_num, &insert);
	if (ret_num) {
		for (int i = 0; i < ret_num; i++) {
			printf("[%d,%d]\t", ret[i].start, ret[i].end);
		}
		printf("\n");

		free(ret);
	}
}
