#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

int nDir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
static char ** visited;


#define isValid(x, y) (x >= 0 && x < m && y >= 0 && y < n)

static bool getWordSearch(char **mz, int m, int n, int x, int y, char * word, int index)
{
	int nx, ny;

	if (index == strlen(word) - 1) {
		return mz[x][y] == word[index];
	}

	if (mz[x][y] == word[index]) {

		visited[x][y] = true;
		for (int i = 0; i < 4; i++) {
			nx = x + nDir[i][0];
			ny = y + nDir[i][1];
			if (isValid(nx, ny) && visited[nx][ny] == 0 && getWordSearch(mz, m, n, nx, ny, word, index+1)) {
				return true;
			}
		}
		// clear. index not increased yet.
		visited[x][y] = false;
	}
	return false;
}

// Offer 12
static bool wordSearch(char **mz, int m, int n, char * word)
{
	int i,j;
	bool ret = false;

	visited = malloc(sizeof(char*) * m);
	for (i = 0; i < m; i++) {
		visited[i] = malloc(n);
		memset(visited[i], 0, n);
	}

	// start point
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (getWordSearch(mz, m, n, i, j, word, 0) == true) {
				ret = true;
				goto out;
			}
		}
	}	

out:
	for (i = 0; i < m; i++) {
		free(visited[i]);
	}
	free(visited);

	return ret;
}

int main(int argc, char **argv)
{
	char *array[] = {"ABCE", "SFCS", "ADEE"};
	//char word[] = "ABCCED";
	char word[] = "SEE";
	//char word[] = "ABCB";

	printf("Has word %s %d\n", word, wordSearch(array, 3, 4, word));
	return 0;
}
