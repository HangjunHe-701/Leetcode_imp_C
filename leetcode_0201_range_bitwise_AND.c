#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// n >= m
// Brian Kernighan's algorithm
unsigned int rangeBitwiseAnd(int m, int n)
{
	if (n == m) return n;

	while (n > m) {
		n &= n -1;
	}
	return n;
}

/*
举个例子，假设区间是 [26,30]，那么这个区间内的数用二进制表示出来为：

11010
11011
11100
11101
11110

可以观察到，把这些数都 AND 起来，只要有 0 的位，最终结果都是 0，所以需要从右往前找到某一位上不为 0 的。
不断的右移左边界和右边界，把右边的 0 都移走，直到它们俩相等，就找到了某一位上开始都不为 0 的了。
在右移的过程中记录下右移了多少位，最后把 m 或者 n 的右边添上 0 即可。
按照上面这个例子来看，11000 是最终的结果。
*/
unsigned int rangeBitwiseAnd1(int m, int n)
{
	int move = 0;

	while (n != m) {
		m >>= 1;
		n >>= 1;
		move++;
	}
	return n << move;
}

unsigned int rangeBitwiseAnd2(int m, int n)
{
	int move = 0xffffffff;

	// != priority higher than &
	while ((n & move) != (m & move)) {
		move <<= 1;
	}
	return n & move;
}

int main(int argc, char **argv)
{
	unsigned int ret; 

	ret = rangeBitwiseAnd2(5, 7);
	printf("The rangeBitwiseAND is 0x%x\n", ret);
}
