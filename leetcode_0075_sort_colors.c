#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


static void sortColors(int *nums, int n)
{
	int r = 0, w = 0, b = 0;

	for (int i = 0; i < n; i ++) {
		if (nums[i] == 0) {
			nums[b++] = 2;
			nums[w++] = 1;
			nums[r++] = 0;	
		} else if (nums[i] == 1) {
			nums[b++] = 2;;
			nums[w++] = 1;
		} else {
			//nums[b++] = 2;
			b++;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int array[] = {2, 2, 1, 2, 0, 0, 1, 1, 2};
	int n = 9;

	sortColors(array, n);
	printf("sort colors\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t", array[i]);
	}
	printf("\n");

	return 0;
}
