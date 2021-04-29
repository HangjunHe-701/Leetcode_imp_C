
// 31 30 29 ... 2 1 0
/*
  异或的特性。第 136，268，389, 421, 1720 题，

	x ^ 0 = x
	x ^ 11111……1111 = ~x
	x ^ (~x) = 11111……1111
	x ^ x = 0
	a ^ b = c  => a ^ c = b  => b ^ c = a (交换律)
	a ^ b ^ c = a ^ (b ^ c) = (a ^ b）^ c (结合律)
*/

/*
  构造特殊 Mask，将特殊位置放 0 或 1。

	将 x 最右边的 n 位清零， x & ( ~0 << n )
	获取 x 的第 n 位值(0 或者 1)，(x >> n) & 1
?	获取 x 的第 n 位的幂值，x & (1 << (n - 1))
	仅将第 n 位置为 1，x | (1 << n)
	仅将第 n 位置为 0，x & (~(1 << n))
	将 x 最高位至第 n 位(含)清零，x & ((1 << n) - 1)
	将第 n 位至第 0 位(含)清零，x & (~((1 << (n + 1)) - 1)）
*/ 

/*
  有特殊意义的 & 位操作运算。第 260 题，第 201 题，第 318 题，第 371 题，第 397 题，第 461 题，第 693 题

	X & 1 == 1 判断是否是奇数(偶数)
	X &= (X - 1) 将最低位(LSB)(last set bit)的 1 清零
	X & -X 得到最低位(LSB)(last set bit)的 1
	X & ~X = 0
	-X == ~(X - 1)
*/

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum{false=0, true=1} bool;
unsigned int leetcode190_reverseBits(unsigned int n) 
{
	unsigned int r = 0;

	for (int i = 0; i < 32; i++) {
		r = (n & 1) | r << 1;
		n >>= 1;
	}
	return r;
}

// The number of ‘1’ bits
unsigned int leetcode191_hammingWeight(unsigned int n) 
{
	unsigned int c = 0;

	while (n) {
		c++;
		n &= n - 1;
	}

	return c;
}

/*
 * n & (n - 1) == 0
 */
bool leetcode231_isPowerOfTwo(int n) 
{
	return (n > 0 && ((n &= n - 1) == 0));
}

/*
 * 1. x is power of 2;
 * 2. x-1 can be divided by 3
 */
int isPowerOfFour(int n)
{
	return n > 0 && (n & n - 1) == 0 && (n - 1) % 3 == 0;
}

// only one 1 bit
bool leetcode231_isPowerOfTwo2(int n) 
{ 
	int cnt = 0; 

	while (n > 0) { 
		cnt += (n & 1); 
		n >>= 1; 
	} 
	return cnt == 1; 
} 

bool leetcode_isPowerOfK(int n, int k) 
{ 
	if (n < 0) {
		return false;
	}

	while (n % k == 0) { 
		n /= k;
	} 
	return n == 1; 
} 

int leetcode268_missingNumber(int *nums, int n) 
{ 
	int i, result=0;

	for (i = 0; i < n; i++){
		result = result ^ nums[i] ^ i;
	}
	return result ^ i; 
}

char leetcode389_findTheDifference(char *s1, char *s2) 
{ 
	int i, n=strlen(s1);
	int result = 0;

	for (i = 0; i < n; i++){
		result ^= s1[i] ^ s2[i];
	}

	return (char)result ^ s2[i]; 
}  

int leetcode461_hammingDistance(int n, int m) 
{
	int temp = m ^ n;
	int count = 0;
	
	while (temp) {
		count ++;
		temp = temp & (temp - 1);
	}
	return count;
}

int leetcode476_findComplement(int n) 
{
	unsigned int mask = ~0;
	
	while (mask & n) {
		mask <<= 1;	
	}

	return ~(mask ^ n);
}

int leetcode476_findComplement2(int n) 
{
	int mask = 1;

	while (mask < n) {
		mask <<= 1;
	}

	return (~n) & (mask - 1);
}

bool leetcode493_hasAlternatingBits(int n) 
{
	/*
	   n =         1 0 1 0 1 0 1 0
	   n >> 1      0 1 0 1 0 1 0 1
	   n ^ n>>1    1 1 1 1 1 1 1 1
	   m           1 1 1 1 1 1 1 1
	   m + 1     1 0 0 0 0 0 0 0 0
	   m & (m+1)   0 0 0 0 0 0 0 0
	*/
	unsigned int mask;

	mask = n ^ (n >> 1);
	return ((mask + 1) & (mask)) == 0;
}

// right shift: even -> odd -> even -> odd
bool leetcode493_hasAlternatingBits2(int n) 
{
	int cur;

	while (n > 0) {
		cur = n & 1;
		//n /= 2;
		n >>= 1;
		if (cur == (n & 1))
			return false;
	}
	return true;
}

// encoded[i] = arr[i] XOR arr[i + 1] -> arr[i + 1] = encoded[i] XOR arr[i] 
int *leetcode1720_decode(int* nums, int n, int k) 
{
	int *ret = malloc(sizeof(int) * (n + 1));

	ret[0] = k;
	for (int i = 1; i <= n; i++) {
		ret[i] = nums[i-1] ^ ret[i-1]; 
	}
	return ret;
}

int main(int argc, char **argv)
{
	//unsigned int n = 0x12345678; 
	unsigned int n = 0x1e6a2c48;
	unsigned int ret, count; 
	bool result = 0x7f;
	int nums[] = {0,1,2,3,5,7,6};

	printf("The lbs is 0x%x & %x-> %x\n", result, -result, result & -result);
	printf("The onebit is 0x%x & %x-> %x\n", result, ~(result-1), result & ~(result-1));

	count = leetcode191_hammingWeight(n);
	printf("The 0x%x 1 bits %d\n", n, count);
	ret = leetcode190_reverseBits(n);
	count = leetcode191_hammingWeight(n);
	printf("The reversed is 0x%x 1 bits %d\n", ret, count);
	n = 16; 
	printf("The %d power of two %d\n", n, leetcode231_isPowerOfTwo(n));

	printf("The %d is power of four %d\n", n, isPowerOfFour(n));

	int k = 4;
	printf("The %d power of %d %d\n", n, k, leetcode_isPowerOfK(n, k));

	ret = leetcode268_missingNumber(nums, 7);
	printf("The missing num is %d\n", ret);

	char s1[] = "hello";
	char *s2 = "hoello";
	printf("The different between %s vs %s is %c\n", s1, s2, leetcode389_findTheDifference(s1, s2));

	printf("The hammingDistance is %d\n", leetcode461_hammingDistance(1, 4));

	k = 5;
	printf("The complement of %d is %d\n", k, leetcode476_findComplement(k));
	printf("The complement of %d is %d\n", k, leetcode476_findComplement2(k));

	k = 11;
	printf("%d is alternating %d\n", k, leetcode493_hasAlternatingBits(k));
	printf("%d is alternating %d\n", k, leetcode493_hasAlternatingBits2(k));

	int encode[] = {6,2,7,3};
	int *ret2 = leetcode1720_decode(encode, 4, 4);
	printf("decode\n");
	for (k = 0; k <= 4; k++) {
		printf("%d\t", ret2[k]);
	}
	printf("\ndecode end\n");
}
