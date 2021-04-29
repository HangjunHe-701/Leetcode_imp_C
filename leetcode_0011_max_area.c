#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int max_area(int* nums, int numSize)
{
	int start = 0, end = numSize - 1;
    int weight, height, max = 0, temp;
		
	while (start < end) {
        weight = end - start;

		if (nums[start] < nums[end]) {
            height = nums[start];
            start++; 
		} else {
            height = nums[end];
            end --;
        }

        temp = height * weight;
        if (temp > max)
            max = temp;
	}

	return max;
}

int main(int argc, char **argv)
{
    int array[] = {438,507,629,255,813,423,536,428,340,767,208,808,882,142,835,423,331,545,627};
    //int array[] = {3,2,4};
    size_t n = sizeof(array)/sizeof(int);

    int result = max_area(array, (int)n);
    printf("max area is: %d\n", result);
}


