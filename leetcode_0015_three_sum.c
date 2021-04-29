// build with bubble_sort.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"


static int ret_index = 0;
int ** three_sum(int* nums, int n)
{
	int start, end=n-1;
    int index = 1;
    int  i = 0;
	int **ret;

	ret = malloc(sizeof(int *) * n);
    // sort the array
	bubble_sort(nums, n);

	for (index = 1; index < n - 1; index++) {
        start = 0;
        end = n -1;

        if (index > 1 && nums[index] == nums[index-1]) {
			// first two are equal
            start = index - 1;
        }

        while (start < index && end > index) {
			// skip duplicated
            if (start > 1 && nums[start] == nums[start-1]) {
                start ++;
                continue;
            }
			// skip duplicated
            if (end < n - 1 && nums[end] == nums[end+1]) {
                end --;
                continue;
            }
			int sum = nums[index] + nums[start] + nums[end]; 
            if (sum == 0) {
				ret[ret_index] = malloc(sizeof(int) * 3);
				ret[ret_index][0] = nums[start];
				ret[ret_index][1] = nums[index];
				ret[ret_index][2] = nums[end];
				ret_index++;
                break;
            }
            else if (sum > 0) {
                end --;
            } else
                start ++;
        }
	}

	return ret;
}

int main(int argc, char **argv)
{
    //int array[] = {-1,-2,3,1,-1,-2,0,2,4};
    int array[] = {-1, 0, 1, 2, -1, -4, 0, 0};
    size_t n = sizeof(array)/sizeof(int);

    int **ret = three_sum(array, (int)n);
    printf("3 sum results %d:\n", ret_index);
	for (int i = 0; i < ret_index; i++) {
		printf("%d %d %d\n", ret[i][0], ret[i][1], ret[i][2]);
	}
}


