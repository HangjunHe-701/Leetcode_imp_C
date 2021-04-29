#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


int dailyTemperatures(int n[], int k, int m[])
{
	int i, j; 

	for (i = 0; i < k; i++) {
		for (j = i+1; j < k; j++) {
			if (n[j] > n[i]) {
				m[i] = j - i;
				break;
			}
		}
	}
	return 0;
}

int leetcode503_nextGreaterElements(int n[], int k, int m[])
{
	int i, j; 

	for (i = 0; i < k; i++) {
		for (j = i+1; j < k; j++) {
			if (n[j] > n[i]) {
				m[i] = n[j];
				break;
			}
		}
		if (m[i]) continue; // need round?
		// next round
		for (j = 0; j < i; j++) {
			if (n[j] > n[i]) {
				m[i] = n[j];
				break;
			}
		}
	}
	return 0;
}

#if 0
// 解法二 单调栈
func dailyTemperatures1(T []int) []int {
	res := make([]int, len(T))
	var toCheck []int
	for i, t := range T {
		// get the head 
		for len(toCheck) > 0 && T[toCheck[len(toCheck)-1]] < t {
			idx := toCheck[len(toCheck)-1]
			res[idx] = i - idx
			// pop
			toCheck = toCheck[:len(toCheck)-1]
		}
		// push stack
		toCheck = append(toCheck, i)
	}
	return res
}
#endif

int main(int argc, char **argv)
{
	int g[]= {73, 74, 75, 71, 69, 72, 76, 73};
	int r[]= {0,0,0,0,0,0,0,0};
	int ret, n=8;

	//dailyTemperatures(g, n, r);
	leetcode503_nextGreaterElements(g, n, r);
	printf("numComponets %d\n", n);
	for (int i=0; i<n; i++)
		printf("%d\t", r[i]);
	printf("\n");
}
