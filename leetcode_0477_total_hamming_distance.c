#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
这道题的关键是找任意两个数的不同的比特位数，所以对于两个数来说，只要比特位有一处不同就加一。
那对于很多个数来说，相当于32个比特位其实都是独立关系的，所以可以拆开来看。
把比特位是0和1的分成两拨，各自组合就可以了，即one*zero
*/
int totalHammingDistance(int * nums, int n)
{
	int i, j;
	int mask;
	int total = 0;
	int tmp;

	for (i = 0; i < 32; i++) {
		mask = 1 << i;
		
		tmp = 0;
		for (j = 0; j < n; j++) {
			if (mask & nums[j])	
				tmp++;
		}
		total += tmp * (n - tmp);
	}

	return total;
}

int main(int argc, char **argv)
{
	int nums[] = {4, 14, 2};
	int ret = totalHammingDistance(nums, 3); 
	printf("The total hanming Distance is %d\n", ret);
}
