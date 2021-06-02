
#include <stdio.h>
#include <stdlib.h>

#define N 10
int final_path[N][N] = {0};  

typedef  enum {false=0, true=1} bool;

// This is predefined
int m[10][10] = {
	0,	1,	1,	0,	1,	1,	1,	1,	0,	1,
	0,	1,	0,	0,	0,	0,	1,	1,	1,	1,
	0,	1,	0,	0,	1,	0,	1,	1,	1,	1,
	0,	0,	0,	1,	1,	0,	1,	1,	1,	1,
	0,	1,	1,	1,	0,	0,	1,	0,	0,	1, //5
	1,	1,	1,	1,	0,	1,	1,	0,	0,	1,
	1,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	0,	0,	1,	1,	1,	1,	0,	1,
	0,	1,	1,	0,	1,	1,	1,	1,	0,	1,
	0,	1,	1,	1,	1,	1,	1,	1,	0,	0
};

void show_path(int maze[][10]) {

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++)
	  		printf ("%d ", maze[i][j]);

	  printf ("\n");
   }
}

/* function to check place is inside the maze and have value 0 */
bool is_valid_place(int x, int y) 
{ 	 
	if (x >= 0 && x < N && y >= 0 && y < N && m[x][y] == 0) {
		
		return true;
	}

	return false;
}

static bool done = false;

int maze(int x, int y)
{
	if (done) return 0;

	if ((y == N - 1) && (x == N - 1)) { //when (x,y) is the bottom right room
		//show_path();
		done = true;
		return 0;
	}
	
	if (is_valid_place (x, y)) {
		final_path[x][y] = 1; //set value
		//printf ("set value on [%d][%d]\n", x, y);
	}

	if (is_valid_place(x, y + 1) && (final_path[x][y + 1] == 0)) {
		//move forward
		maze(x, y + 1);
	}
	if (is_valid_place(x + 1, y) && (final_path[x + 1][y] == 0)) {
		//move down
		maze(x + 1, y);
	} 
	if (is_valid_place(x , y - 1) && (final_path[x][y - 1] == 0)) {
		//move backward
		maze(x, y - 1);
	}
	if (is_valid_place(x - 1, y) && (final_path[x - 1][y] == 0)) {
		//move up
		maze(x - 1, y);
	} 
	
	//no way, go back
	if (!done) {
		final_path[x][y] = 0; //clear value
		//printf ("clear value from [%d][%d]\n", x, y);
	}
	return 1;
}

#if 1 
int m2[10][10] = {
	0,	1,	1,	0,	1,	1,	1,	1,	0,	1,
	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,
	0,	1,	0,	1,	1,	0,	1,	1,	1,	1,
	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,
	0,	1,	1,	1,	0,	0,	1,	0,	0,	1, //5
	1,	1,	1,	1,	0,	1,	1,	0,	0,	1,
	1,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	0,	0,	1,	1,	1,	1,	0,	1,
	0,	1,	1,	0,	1,	1,	1,	1,	0,	1,
	0,	1,	1,	1,	1,	1,	1,	1,	0,	0
};
#else
int m2[3][3] = {
  0,0,0,
  0,1,0,
  0,0,0
};
#endif
static void getUniquePaths(int x, int m, int y, int n, int *ret_count)
{
	//if (x > m || y > n) return;

	if (x == m -1 && y == n - 1) {
		(*ret_count) ++;
		return;
	}
	// right
	if  (y+1 < n && m2[x][y+1] == 0) {
		getUniquePaths(x, m, y+1, n, ret_count);
	}	
	// down
	if  (x+1 < m && m2[x+1][y] == 0) {
		getUniquePaths(x+1, m, y, n, ret_count);
	}	

	return;	
}

static int uniquePaths(int m, int n)
{
	int ret_count = 0;
	getUniquePaths(0, m, 0, n, &ret_count);

	return ret_count;
}

// DP sulution
static int uniquePaths2(int m, int n)
{
	int ** dp;
	int i,j;
	int ret;

	if (m2[0][0] == 1) return 0;

	dp = malloc(sizeof(int *) * m);
	for (i = 0; i < m; i++) {
		dp[i] = malloc(sizeof(int) * n);
	}

	// first row 
	for (i = 0; i < n; i++) {
		if (m2[0][i])
			dp[0][i] = 0;
		else
			dp[0][i] = 1;
	}
	// first column
	for (i = 0; i < m; i++) {
		if (m2[i][0] == 1)
			dp[i][0] = 0;
		else
			dp[i][0] = 1;
	}

	for (i = 1; i < m; i++) {
		for (j = 1; j < n; j++) {
			if (m2[i][j])
				dp[i][j] = 0;
			else
				dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}

	ret = dp[m-1][n-1];

	for (i = 0; i < m; i++) {
		free(dp[i]);
	}
	free(dp);

	return ret;
}

int main()
{
	show_path(m);
	maze(0, 0);
	printf("\nsolution:\n");
	show_path(final_path);
	
	// leetcode
	printf("\nm2:\n");
	show_path(m2);
	int len = 10;
	printf("\nRecur: unique paths of m2 is %d\n", uniquePaths(len, len));
	printf("\nDP: unique paths of m2 is %d\n", uniquePaths2(len, len));
    return 0;
}

