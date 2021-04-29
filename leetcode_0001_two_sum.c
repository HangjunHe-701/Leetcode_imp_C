#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int* two_sum(int* nums, int numSize, int target)
{
	int temp, i;
	int* solution = NULL;

	// wrong, num maybe nagative or zero???
	int * map = malloc(sizeof(int) * target);
	if (!map) 
		return NULL;
		
	//memset(map, 0, sizeof(int)*target);
	for (i = 0; i < target; i++) {
		map[i] = -1;
	}
		
	for (i = 0; i < numSize; i++) {

		if (nums[i] > target)
			continue;
		
		temp = target - nums[i];
		//if (map[temp] != i && temp == nums[map[temp]]) {
		if (temp == nums[map[temp]]) {
			/* hit */
			solution = (int *)malloc(sizeof(int) * 2);
			
			solution[0] = map[temp];
			solution[1] = i;
			goto out;
		}

		map[nums[i]] = i;
	}

out:
 	free(map);
	return solution;
}

int main(int argc, char **argv)
{
    //int array[] = {438,507,629,255,813,423,536,428,340,767,208,808,882,142,835,423,331,545,627};
    int array[] = {0,5,6,2,4};
    size_t n = sizeof(array)/sizeof(int);
    int target = 5;

    int* result = two_sum(array, (int)n, target);
    if (NULL != result)
    {
        printf("The index1: %d; the index2: %d\n", result[0], result[1]);
        printf("values are %d and %d.\n", array[result[0]], array[result[1]]);
        free(result);//memory deallocation
    }else
    {
        printf("result is not available!\n");
    }
}


