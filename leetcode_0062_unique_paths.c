#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 


static void getUniquePaths(int x, int y, int m, int n, int *count)
{
	//if (x >= m || y >= n) return;

	if (x == m - 1 && y == n - 1) {
		(*count) ++;
		return;
	}
	if (x < m - 1)
		getUniquePaths(x+1, y, m, n, count);
	if (y < n - 1)
		getUniquePaths(x, y+1, m, n, count);
}

static int uniquePaths(int m, int n) 
{
	int count = 0;

	getUniquePaths(0, 0, m, n, &count);
	return count;
}

/*
这是一道简单的 DP 题。输出地图上从左上角走到右下角的走法数。
由于机器人只能向右走和向下走，所以地图的第一行和第一列的走法数都是 1，地图中任意一点的走法数是 dp[i][j] = dp[i-1][j] + dp[i][j-1]
*/
static int uniquePaths2(int m, int n) 
{
	int count = 0;
	int ** dp;
	int i, j;

	dp = malloc(sizeof(int *) *m);
	for (i = 0; i < m; i++) {
		dp[i] = malloc(sizeof(int) * n); 
	}

	// known dps!!! 
	for (i = 0; i < m; i++) {
		dp[i][0] = 1; 
	}
	for (i = 0; i < n; i++) {
		dp[0][i] = 1; 
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1]; 
		}
	}
	return dp[m-1][n-1];
}

int main(int argc, char **argv)
{
	int ret;
	int m = 3, n = 3;

	ret = uniquePaths(m, n);
	printf("Recur uniquePaths %d\n", ret);
	printf("DP uniquePaths %d\n", uniquePaths2(m, n));
	return 0;
}
