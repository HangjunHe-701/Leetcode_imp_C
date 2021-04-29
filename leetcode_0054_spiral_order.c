#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 


static int * spiralOrder(int nums[][4], int m, int n)
{
	int *ret, i;
	int spDir[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};
	int round = 0;
	int x = 0, y = 0;
	int **visited;

	ret = malloc(sizeof(int) * m *n);
	// failed

	if (m == 1 && n == 1) {
		ret[0] = nums[0][0];
		return ret;
	}
	if (m == 1) {
		for (i = 0; i < n; i++) { 
			ret[i] = nums[0][i];
		}
		return ret;
	}
	if (n == 1) {
		for (i = 0; i < m; i++) { 
			ret[i] = nums[i][0];
		}
		return ret;
	}
	visited = malloc(sizeof(int*) * m);
	for (i = 0; i < m; i ++) {
		visited[i] = malloc(sizeof(int) * n);	
		memset(visited[i], 0, sizeof(int) * n);
	}

	ret[0] = nums[0][0];
	visited[0][0] = 1;
	for (i = 1; i < m*n; i++) {
		// update x, y
		x += spDir[round%4][0];
		y += spDir[round%4][1];	

		if (x == 0 && y == n - 1 || x == m - 1 && y == n - 1 || x == m - 1 && y == 0) {
			round++;
		}
		if (x > m-1 || y > n-1 || x < 0 || y < 0) {
			return ret; 
		}
		if (visited[x][y] == 0) {
			visited[x][y] = 1;
			ret[i] = nums[x][y];
		}
		
		switch(round%4) {
			case 3:
				if (x - 1 >= 0 && visited[x-1][y] == 1)	
					round++;
				break;
			case 2:
				if (y - 1 >= 0 && visited[x][y-1] == 1)	
					round++;
				break;
			case 1:
				if (x + 1 <= n - 1 && visited[x+1][y] == 1)	
					round++;
				break;
			default:
				if (y + 1 <= m - 1 && visited[x][y+1] == 1)
					round++;
				break;

		}
	}

	return ret;	
}


int main(int argc, char **argv)
{
	int array[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	int *ret;

	ret = spiralOrder(array, 3, 4);
	for (int i = 0; i < 3* 4; i ++) {
		printf("%d\t", ret[i]);
	}
	printf("\n");

	free(ret);
	return 0;
}
