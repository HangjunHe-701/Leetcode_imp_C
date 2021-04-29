#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

/*
把加减运算符号后面的数字压入栈中，遇到乘除运算，直接将它与栈顶的元素计算，并将计算后的结果放入栈顶。
若读到一个运算符，或者遍历到字符串末尾，即认为是遍历到了数字末尾。
处理完该数字后，更新 preSign 为当前遍历的字符。
遍历完字符串 s 后，将栈中元素累加，即为该字符串表达式的值。
时间复杂度 O(n)，空间复杂度 O(n)。
*/


int calculate(char* s)
{
	int len = strlen(s);
	int * buf = malloc(sizeof(int) *len);
	char presign = '+';
	int num = 0;
	int ret = 0, i;
	int isdigit, index = 0;
	
	for (i = 0; i < len; i++) {

		isdigit = (s[i] >= '0' && s[i] <= '9') ? 1 : 0;;
		if (isdigit) {
			num = num * 10 + s[i] - '0';
		} 

		// the last char is blank, i.e. " 3+5 / 2 "
		if (((s[i] != ' ') && !isdigit) || i == len - 1) {

			switch (presign) {
				case '+':
					buf[index++] = num;
					break;
				case '-':
					buf[index++] = -num;
					break;

				case '*':
					buf[index-1] *= num;
					break;

				default: /* division */
					buf[index-1] /= num;
					break;
			}
			num = 0;
			presign = s[i];
		}
	}
	printf("index %d\n", index);
	for (i = 0; i < index; i++) {
		ret += buf[i];
	}

	free(buf);
	return ret;
}

int main(int argc, char **argv)
{
    char array[] = " 3+5 / 2 ";
    //char array[] = "3+2*2";

    printf("The \"%s\" calc to %d\n", array, calculate(array));

}


