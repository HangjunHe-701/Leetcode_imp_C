#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


/*
    要求不用加法和减法运算符计算 a+b。这一题需要用到 ^ 和 & 运算符的性质:
	两个数 ^ 可以实现两个数不带进位的二进制加法。这里需要实现加法，肯定需要进位。
	所以如何找到进位是本题的关键。
    在二进制中，只有 1 和 1 加在一起才会进位，0 和 0，0 和 1，1 和 0，这三种情况都不会进位，规律就是 a & b 为 0 的时候就不用进位，为 1 的时候代表需要进位。
	进位是往前进一位，所以还需要左移操作，所以加上的进位为 (a&b)<<1。
*/
int getSum(int n, int m)
{
	int sum = n ^ m, carry = n & m;
	int temp;

	while (carry) {
		temp = sum;
		sum ^= carry << 1;
		carry = temp & (carry << 1);
	}

	return sum;	
}

// recursive
int getSum2(int n, int m)
{
	if (n == 0)
		return m;
	if (m == 0)
		return n;

	return getSum2(n^m, (n&m)<<1);
}

int main(int argc, char **argv)
{
	int n = 16, m = 8;

	printf("The %d + %d is  %d\n", n, m, getSum(n, m));
	printf("The %d + %d is  %d\n", n, m, getSum2(n, m));
}
