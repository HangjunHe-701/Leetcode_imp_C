#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

int spDir[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}}; 

// Offer 29
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

static void printfMatrixClockwisely(int **nums, int rows, int columns, int start)
{
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;
	int i;

	// left -> right
	for (i = start; i <= endX; ++i) {
		printf("%d\t", nums[start][i]);
	}
	// up -> down 
	if (start < endY) {
		for (i = start + 1; i <= endY; ++i) {
			printf("%d\t", nums[i][endX]);
		}
	}
	// left <- right
	if (start < endX && start < endY) {
		for (i = endX - 1; i >= start; --i) {
			printf("%d\t", nums[endY][i]);
		}
	}
	// up <- down 
	if (start < endY - 1 && start < endX) {
		for (i = endY - 1; i > start; --i) {
			printf("%d\t", nums[i][start]);
		}
	}
}
void offer29_printMatrixClockwisely(int **nums, int rows, int columns)
{
	int start = 0;
	if (nums == NULL || rows <= 0 || columns <= 0)
		return;

	while (rows > 2 * start && columns > 2 * start) {
		printfMatrixClockwisely(nums, rows, columns, start);
		start ++;
	}
	return;
}

int main(int argc, char **argv)
{
	int i, j;
	int **ret;
	int n = 5;

	ret = spiral_matrix(n);
#if 1
	for (i = 0; i < n; i ++) {
		for (j = 0; j < n; j ++) {
			printf("%d\t", ret[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	offer29_printMatrixClockwisely(ret, n, n);
	printf("\n");

	for (i = 0; i < n; i++) {
		free(ret[i]);
	}
	free(ret);
#endif
}
