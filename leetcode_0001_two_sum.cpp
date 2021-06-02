#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <map>
using namespace std;

int* leetcode0001_twoSum(int* nums, int numSize, int target)
{
	int temp, i;
	int* solution = NULL;
	map<int,int> map1;
	map<int,int>::iterator it;

	for (i = 0; i < numSize; i++) {

		if (nums[i] > target)
			continue;
		
		temp = target - nums[i];
		it = map1.find(temp);
		//if (it != map1.end() && temp == (*it).first) {
		if (it != map1.end()) {
			/* hit */
			solution = (int *)malloc(sizeof(int) * 2);
			
			solution[1] = i;
			solution[0] = (*it).second;
			goto out;
		}
		map1.insert(pair<int,int>(nums[i], i));
	}

out:
	return solution;
}

int* offer57_twoSum(int* nums, int numSize, int target)
{
	int left = 0, right = numSize-1;
	int* solution = NULL;

	while (left < right) {
		
		if (nums[left] + nums[right] == target) {
			/* hit */
			solution = (int *)malloc(sizeof(int) * 2);
			
			solution[1] = nums[right];
			solution[0] = nums[left];
			goto out;
		}
		if (nums[left] + nums[right] > target) {
			right--;
		} else {
			left++;
		}
	}

out:
	return solution;
}
int main(int argc, char **argv)
{
    //int array[] = {438,507,629,255,813,423,536,428,340,767,208,808,882,142,835,423,331,545,627};
    int array[] = {0,5,6,2,4};
    int array2[] = {1,2,4,7,11,15};
    size_t n = sizeof(array)/sizeof(int);
    size_t n2 = sizeof(array2)/sizeof(int);
    int target = 5;
    int target2 = 15;

    int* result = offer57_twoSum(array2, (int)n2, target2);
    if (NULL != result)
    {
        printf("Offer 57 The index1: %d; the index2: %d\n", result[0], result[1]);
        printf("values are %d and %d.\n", array[result[0]], array[result[1]]);
        free(result);//memory deallocation
    }else
    {
        printf("result is not available!\n");
    }

    result = leetcode0001_twoSum(array, (int)n, target);
    if (NULL != result)
    {
        printf("Leetcode 0001 The index1: %d; the index2: %d\n", result[0], result[1]);
        printf("values are %d and %d.\n", array[result[0]], array[result[1]]);
        free(result);//memory deallocation
    }else
    {
        printf("result is not available!\n");
    }
}


