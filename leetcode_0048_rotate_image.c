#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
 * clockwise rotate 顺时针旋转
 * first reverse up to down, then swap the symmetry 
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
    
/*
 * anticlockwise rotate 逆时针旋转
 * first reverse left to right, then swap the symmetry
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/
// the right must be [4] 
static void anticlockwiseRotate(int nums[][4], int n)
{
	int i, j;
	int temp;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n/2; j++) {
			// reverse right to left
			temp = nums[i][j];
			nums[i][j] = nums[i][n - 1 - j];
			nums[i][n - 1 -j] = temp;
		}
	}

	// swap symmetry
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			temp = nums[i][j];
			nums[i][j] = nums[j][i];
			nums[j][i] = temp;
		}
	}

	return;
}

static void rotate(int nums[][4], int n)
{
	int i, j;
	int * tmp;
	int temp;

	tmp = malloc(sizeof(int) * n);

	for (i = 0; i < n/2; i++) {
		// reverse up to down
		memcpy(tmp, nums[i], sizeof(int)*n);
		memcpy(nums[i], nums[n-1-i], sizeof(int)*n);
		memcpy(nums[n-1-i], tmp, sizeof(int)*n);
	}
	// swap symmetry
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			temp = nums[i][j];
			nums[i][j] = nums[j][i];
			nums[j][i] = temp;
		}
	}

	return;
}

int main(int argc, char **argv)
{
	int array[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
	int array2[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};

	printf("before rotate\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf ("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	rotate(array, 4);

	printf("after rotate\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf ("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("before anticlock rotate\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf ("%d\t", array2[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	anticlockwiseRotate(array2, 4);

	printf("after anticlock rotate\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf ("%d\t", array2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
