#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

int spDir[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}}; 

static int** spiral_matrix(int n) 
{
	int ** ret;
	int ** visited;
	int i, x=0, y=0, round = 0;

	ret = malloc(sizeof(int *) *n);
	for (i = 0; i < n; i++) {
		ret[i] = malloc(sizeof(int) * n);
	}

	visited = malloc(sizeof(int *) *n);
	for (i = 0; i < n; i++) {
		visited[i] = malloc(sizeof(int) * n);
		memset(visited[i], 0, sizeof(int) * n);
	}

	ret[0][0] = 1;
	visited[0][0] = 1;

	for (i = 1; i < n*n; i++) {
		x += spDir[round%4][0];
		y += spDir[round%4][1];	

		if (x < 0 || y < 0 || x > n-1 || y > n-1) {
			goto out;
		}
		if ((x == 0 && y == n - 1) || (x == n -1 && y == n -1) || (x == n -1 && y == 0)) {
			round++;
		}

		if (visited[x][y] == 0) {
			ret[x][y] = i+1;
			visited[x][y] = 1;
		}

		switch(round%4) {
			case 0:
				if (y < n - 1 && visited[x][y+1] == 1) {
					round++;
				}
				break;
			case 1:
				if (x < n - 1 && visited[x+1][y] == 1) {
					round++;
				}
				break;
			case 2:
				if (y > 0 && visited[x][y - 1] == 1) {
					round++;
				}
				break;
			default:
				if (x > 0 && visited[x-1][y] == 1) {
					round++;
				}
				break;
		}
	}

out:
	for (i = 0; i < n; i++) {
		free(visited[i]);
	}
	free(visited);

	return ret;
}


int main(int argc, char **argv)
{
	int i, j;
	int **ret;
	int n = 10;

	ret = spiral_matrix(n);
#if 1
	for (i = 0; i < n; i ++) {
		for (j = 0; j < n; j ++) {
			printf("%d\t", ret[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < n; i++) {
		free(ret[i]);
	}
	free(ret);
#endif
}
