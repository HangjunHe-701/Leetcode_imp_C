#include <stdio.h>

//冒泡 
int bubble_sort(int *nums, int n)
{ 
	int i;
	int j;
	int tmp;

	printf("\n before sorted:\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", nums[i]);
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (nums[j] > nums[j+1]) {
				tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = tmp;
			}
		}
	}
	printf("\n after sorted:\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", nums[i]);
	}
	printf("\n");
	return 0;
}
