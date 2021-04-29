#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
 * 用数组模拟乘法。创建一个数组长度为 len(num1) + len(num2) 的数组用于存储乘积。
 * 对于任意 0 ≤ i < len(num1)，0 ≤ j < len(num2)，num1[i] * num2[j] 的结果位于 tmp[i+j+1]，
 * 如果 tmp[i+j+1]≥10，则将进位部分加到 tmp[i+j]。最后，将数组 tmp 转成字符串，如果最高位是 0 则舍弃最高位。
 */
char * multiply(char *s, char *t)
{
	char *ret;
	int lenS = strlen(s);
	int lenT = strlen(t);
	int *intR; 
	int i, j;
	int head_zero = 0;

	ret = malloc(lenS + lenT + 1);
	
	intR = malloc(sizeof(int) * (lenT + lenS));
	memset(intR, 0, sizeof(int) * (lenT + lenS));

	for (i = lenS - 1; i >= 0; i--) {
		for (j = lenT - 1; j >= 0; j--) {
			intR[i+j+1] += (s[i]-'0') * (t[j]-'0');

			if (intR[i+j+1] >= 10) {
				intR[i+j] +=  (intR[i+j+1] / 10);
				intR[i+j+1] %= 10;
			}
		}
	}

	if (intR[0] == 0) head_zero = 1;

	for (i = 0; i < lenT + lenS - head_zero; i++) {
		ret[i] = (char)intR[i+head_zero] + '0';
	}
	ret[i] = '\0';

	free(intR);
	return ret;
}


int main(int argc, char **argv)
{
	char s[] = "123";
	char t[] = "456";
	char * ret = multiply(s, t);

	printf("%s * %s = %s\n", s, t, ret);
	free (ret);
}
