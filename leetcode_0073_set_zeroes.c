#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

/*
此题考查对程序的控制能力，无算法思想。题目要求采用原地的算法，所有修改即在原二维数组上进行。
在二维数组中有 2 个特殊位置，一个是第一行，一个是第一列。它们的特殊性在于，它们之间只要有一个 0，它们都会变为全 0 。
先用 2 个变量记录这一行和这一列中是否有 0，防止之后的修改覆盖了这 2 个地方。
然后除去这一行和这一列以外的部分判断是否有 0，如果有 0，将它们所在的行第一个元素标记为 0，所在列的第一个元素标记为 0 。
最后通过标记，将对应的行列置 0 即可。
*/
static void setZeroes(int nums[][4], int m, int n)
{
	int i,j;
	bool firstRawZero = false;
	bool firstColumnZero = false;

	// first row
	for (i = 0; i < n; i++) {
		if (nums[0][i] == 0) {
			firstRawZero = true;
			break;
		}
	}
	// first column 
	for (i = 0; i < m; i++) {
		if (nums[i][0] == 0) {
			firstColumnZero = true;
			break;
		}
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			if (nums[i][j] == 0) {
				nums[0][j] = nums[i][0] = 0;
			}
		}
	}

	// row
	for (i = 0; i < n; i++) {
		if (nums[0][i] == 0) {
			// whole column 
			for (j = 1; j < m; j++) {
				nums[j][i] = 0;
			}
		}
	}
	// column 
	for (i = 0; i < m; i++) {
		if (nums[i][0] == 0) {
			// whole raw
			for (j = 0; j < n; j++) {
				nums[i][j] = 0;
			}
		}
	}

	if (firstRawZero) {
		// first row zero
		for (i = 0; i < n; i++) {
			nums[0][i] = 0;
		}
	}
	if (firstColumnZero) {
		// first row zero
		for (i = 0; i < m; i++) {
			nums[i][0] = 0;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int array[][4] = {{1,2,3,4},{9,9,9,9},{3,0,1,2},{4,5,6,0},{0,1,2,0}};
	int m = 5;
	int n = 4;

	printf("before\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	setZeroes(array, m, n);

	printf("after\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d\t", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
