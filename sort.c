#include <stdio.h>

int partition(int *nums, int start, int end)
{
	int small = start - 1;
	int tmp;

	for (int i = start; i < end; ++i) {
		if (nums[i] < nums[end]) {
			++small;
			if (small != i) {
				tmp = nums[i];
				nums[i] = nums[small];
				nums[small] = nums[i];
			}
		}
	}
	// swap end
	small++;
	tmp = nums[end];
	nums[end] = nums[small];
	nums[small] = nums[end];
	return small;
}
static void quickSort(int *nums, int start, int end)
{ 
	int index;

	if (end <= start) return;
	
	index = partition(nums, start, end);
	quickSort(nums, start, index - 1);
	quickSort(nums, index + 1, end);
}
int quick_sort(int *nums, int n)
{ 
	int i;
	int j;
	int tmp;

	printf("\n before quick sort:\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", nums[i]);
	}
	printf("\n");

	quickSort(nums, 0, n-1);

	printf("\n after sorted:\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", nums[i]);
	}
	printf("\n");
	return 0;
}

//冒泡 
int bubble_sort(int *nums, int n)
{ 
	int i;
	int j;
	int tmp;

	printf("\n before bubble sort:\n");
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
