#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/**
 * BFS: breadth first search
 * DFS: depth first search
 *
 */
/*
 * 假设n个节点存在二叉查找树的个数是G(n)
 * 1为根节点，2为根节点，…，n为根节点
 * 当1为根节点时，其左子树节点个数为0，右子树节点个数为n-1
 * 当2为根节点时，其左子树节点个数为1，右子树节点为n-2
 * 所以可得G(n) = G(0) *G(n-1)+G(1)*(n-2)+...+G(n-1)*G(0)
 */

int numTrees(int n)
{
	int *dp, i, j;

	if (n <= 1) {
		return n; 
	}

	dp = malloc(sizeof(int) * (n+1));
	//failed
	memset(dp, 0, sizeof(int) * (n+1));

	dp[0] = 1;
	dp[1] = 1;

	for (i = 2; i <= n; i++) {
		for (j = 0; j < i; j++) {
			dp[i] += dp[j]*dp[i-j-1];
			printf ("i = %d, dp[] = %d\n", i, dp[i]);
		}
	}
	return dp[n];
}

int main ()
{
	int n=3;

	printf("numTrees: %d, n=%d\n", numTrees(n), n);	
	return 0;
}
