#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

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
			*ret = min((*ret), (count));
		else 
			*ret = count;
		return;
	}

	getUniquePaths(x+1, y, m, n, count + array[x][y], ret);
	getUniquePaths(x, y+1, m, n, count + array[x][y], ret);
}

static int uniquePathsRecur(int m, int n) 
{
	int ret = 0;

	getUniquePaths(0, 0, m, n, 0, &ret);
	return ret;
}

// better, not modify the original array
static int uniquePaths(int m, int n) 
{
	int sum;
	int ** dp;
	int i, j;

	dp = new int*[m];
	for (i = 0; i < m; i++) {
		dp[i] = new int[n]; 
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
			dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + array[i][j]; 
		}
	}
	sum = dp[m-1][n-1];

	for (i = 0; i < m; i++) {
		delete[] (dp[i]); 
	}
	delete[] dp;

	return sum;
}

static int uniquePaths2(int m, int n) 
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
			array[i][j] += min(array[i-1][j], array[i][j-1]); 
		}
	}
	sum = array[m-1][n-1];

	return sum;
}

// wrong
int offer47_getMaxValue(int rows, int cols)
{
    if(array == nullptr || rows <= 0 || cols <= 0)
        return 0;             

    int* maxValues = new int[cols];
    for(int i = 0; i < rows; ++i)  
    {  
        for(int j = 0; j < cols; ++j)  
        {
            int left = 0;     
            int up = 0;

            if(i > 0)
                up = maxValues[j];             

            if(j > 0)
                left = maxValues[j - 1];       

            //maxValues[j] = std::max(left, up) + array[i][j];
            maxValues[j] = std::min(left, up) + array[i][j];
        }
    }

    int maxValue = maxValues[cols - 1];

    delete[] maxValues;

    return maxValue;
}

int main(int argc, char **argv)
{
	int ret;
	int m = 3, n = 3;

	ret = uniquePaths(m, n);
	printf("minimal sum %d\n", ret);
	printf("minimal sum %d\n", uniquePathsRecur(m, n));
	//printf("minimal sum %d\n", uniquePaths2(m, n));
	printf("offer47 minimal sum %d\n", offer47_getMaxValue(m, n));

	return 0;
}
