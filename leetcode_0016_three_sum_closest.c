// build with bubble_sort.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"


static int compare_minus(int a, int b) {
    if  (a >= b) return a - b;
    else return b - a;
}

int three_sum_c(int* nums, int n, int target)
{
	int start, end=n-1;
    int index = 1;
    int  i = 0;
    int  temp, closest=nums[0] + nums[1] + nums[2];

    // sort the array
    while (i < n) {
        printf ("%d ", nums[i++]);
    }
    printf ("\n");
	bubble_sort(nums, n);
    i = 0;
    while (i < n) {
        printf ("%d ", nums[i++]);
    }
    printf ("\n");

	while (index++ < end - 1) {
        start = 0;
        end = n -1;
        if (nums[index] == nums[index+1]) {
            start ++;
            continue;
        }

        while (start < index && end > index) {
            if (nums[start] == nums[start+1]) {
                start ++;
                continue;
            }
            if (nums[end] == nums[end-1]) {
                end --;
                continue;
            }
            temp = nums[index] + nums[start] + nums[end];
            if (compare_minus(temp, target) < compare_minus(closest, target)) {
            
                printf("%d %d %d -> %d t %d\n", nums[start], nums[index], nums[end], closest, temp);
                closest = temp;
            }
            if (temp == target)
                return temp;
            if (temp > target) {
                end --;
            } else
                start ++;
        }
	}

	return closest;
}

int main(int argc, char **argv)
{
    //int array[] = {438,507,629,208,255,813,423,536,428,340,767,208,808,882,142,835,423,331,545,627};
    int array[] = {-1,-2,3,1,-1,-2,0,2,4};
    size_t n = sizeof(array)/sizeof(int);
    int target = 8;

    int result = three_sum_c(array, (int)n, target);
    printf("max area is: %d\n", result);
}


