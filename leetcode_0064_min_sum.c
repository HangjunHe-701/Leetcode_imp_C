#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

static int array[][3] = {
  1,3,1,
  1,5,1,
  4,2,1
};

static void getUniquePaths(int x, int y, int m, int n, int count, int *ret)
{
	if (x >= m || y >= n) return;

	if (x == m - 1 && y == n - 1) {
		// add the last node
		count += array[x][y];
		if (*ret)
			*ret = MIN((*ret), (count));
		else 
			*ret = count;
		return;
	}

	getUniquePaths(x+1, y, m, n, count + array[x][y], ret);
	getUniquePaths(x, y+1, m, n, count + array[x][y], ret);
}

static int uniquePaths(int m, int n) 
{
	int ret = 0;

	getUniquePaths(0, 0, m, n, 0, &ret);
	return ret;
}

static int uniquePaths2(int m, int n) 
{
	int sum;
	int ** dp;
	int i, j;

	dp = malloc(sizeof(int *) *m);
	for (i = 0; i < m; i++) {
		dp[i] = malloc(sizeof(int) * n); 
	}

	// known dps!!! 
	// column
	for (i = 0; i < m; i++) {
		if (i == 0)
			dp[i][0] = array[0][0]; 
		else 
			dp[i][0] = array[i][0] + dp[i-1][0]; 
	}
	// row
	for (i = 0; i < n; i++) {
		if (i == 0)
			dp[0][i] = array[0][0]; 
		else 
			dp[0][i] = array[0][i] + dp[0][i-1]; 
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			dp[i][j] = MIN(dp[i-1][j], dp[i][j-1]) + array[i][j]; 
		}
	}
	sum = dp[m-1][n-1];

	for (i = 0; i < m; i++) {
		free(dp[i]); 
	}
	free(dp);

	return sum;
}

static int uniquePaths3(int m, int n) 
{
	int sum;
	int i, j;

	// column
	for (i = 1; i < m; i++) {
		array[i][0] += array[i-1][0]; 
	}
	// row
	for (i = 1; i < n; i++) {
		array[0][i] += array[0][i-1]; 
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			array[i][j] += MIN(array[i-1][j], array[i][j-1]); 
		}
	}
	sum = array[m-1][n-1];

	return sum;
}

int main(int argc, char **argv)
{
	int ret;
	int m = 3, n = 3;

	ret = uniquePaths(m, n);
	printf("minimal sum %d\n", ret);
	printf("minimal sum %d\n", uniquePaths2(m, n));
	printf("minimal sum %d\n", uniquePaths3(m, n));
	return 0;
}
