#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
题目给出 [L, R] 区间，在这个区间内的每个整数的二进制表示中 1 的个数如果是素数，那么最终结果就加一，问最终结果是多少？
这一题是一个组合题，判断一个数的二进制位有多少位 1，是第 191 题。
题目中限定了区间最大不超过 10^6 ，所以 1 的位数最大是 19 位，也就是说素数最大就是 19 。那么素数可以有限枚举出来。
最后按照题目的意思累积结果就可以了。
*/
typedef enum {false=0, true=1} bool;

static bool isPrime (int n) 
{
	return (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19);
}

static int bitSetCount(int n)
{
	int count = 0;
	while (n) {
		n &= n - 1;
		count ++;
	}
	return count;
}

int countPrimeSetBits(int l, int r)
{
	int total = 0;

	for (int i = l; i <= r; i++) {
		if (isPrime(bitSetCount(i)))
			total ++; 
	}
	return total;
}

int main(int argc, char **argv)
{
	int l = 10, r = 15;
	int ret = countPrimeSetBits(l, r); 
	printf("The total prime setBit of %d-%d is %d\n", l, r, ret);
}
