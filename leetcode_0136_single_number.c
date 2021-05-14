#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// a ^ a = 0; 0 ^ a = a 
int leetcode136_singleNumber(int nums[], int n) 
{
	int result = 0;
	int i;

	for (i = 0; i < n; i++) {
		result ^= nums[i];	
	}
	return result;
}

// why?
int leetcode137_singleNumber(int nums[], int n) 
{
	int ones = 0, twos = 0;

	for (int i = 0; i < n; i++) {
		ones = (ones ^ nums[i]) & (~twos);
		twos = (twos ^ nums[i]) & (~ones);
	}
	return ones;
}

// 5 same: why?
int leetcode137_singleNumberII(int nums[], int n)
{
    int na = 0, nb = 0, nc = 0;

    for (int i = 0; i < n; i++) {
        nb = nb ^ (nums[i] & na);
        na = (na ^ nums[i]) & ~nc;
        nc = nc ^ (nums[i] & ~na & ~nb);
    }
    return na & ~nb & ~nc;
}

// "x & -x" get lbs (last bit set) 
// Offer 56
int leetcode260_singleNumber(int nums[], int n, int *result1, int *result2) 
{
	int result = 0;
	int i;

	for (i = 0; i < n; i++) {
		result ^= nums[i];	
	}
	result &= (-result);
	for (i = 0; i < n; i++) {
		if (nums[i] & result)
			*result1 ^= nums[i];	
		else
			*result2 ^= nums[i];
	}
	return result;
}

int main(int argc, char **argv)
{
	//int nums[] = {1, 1, 2, 2, 1, 3, 2}; 
	int nums[] = {1, 1, 1,2,2 ,1, 2, 2, 1, 3, 2}; 
	int nums2[] = {1,2,1,3,2,5}; 
	int ret=0, ret2= 0;

	//ret = singleNumber(nums, 5);
	//ret = leetcode137_singleNumber(nums, 7);
	ret = leetcode137_singleNumberII(nums, 11);
	printf("The single number is %d\n", ret);
	ret = 0;
	leetcode260_singleNumber(nums2, 6, &ret, &ret2);
	printf("The single number is %d and %d\n", ret, ret2);
}
