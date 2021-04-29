#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
    这里需要利用位运算 & 运算的性质，如果 X & Y = 0，说明 X 和 Y 完全不相同。
	那么我们将字符串都编码成二进制数，进行 & 运算即可分出没有公共字符的字符串，最后动态维护长度乘积最大值即可。
	将字符串编码成二进制数的规则比较简单，每个字符相对于 ‘a’ 的距离，根据这个距离将 1 左移多少位。

    a 1->1  
    b 2->10  
    c 4->100  
    ab 3->11  
    ac 5->101  
    abc 7->111  
    az 33554433->10000000000000000000000001  
*/

int maxProduct(char *s[], int n)
{
	int max = 0; 
	int i, j;
	int *vector;

	vector = malloc(sizeof(int)*n);
	// failed not considered
    memset(vector, 0, sizeof(int)*n);	

	for (i = 0; i < n; i++) {
		j = 0;
		while (s[i][j]) {
			vector[i] |= 1 << (s[i][j] - 'a');
			j++;
		}
	}

	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
			if ((vector[i] & vector[j]) == 0 && max < strlen(s[i]) * strlen(s[j])) {
				max = strlen(s[i]) * strlen(s[j]);
			}
		}
	}
	return max;
}

int main(int argc, char **argv)
{
	char *s[] = {"abcw","baz","foo","bar","xtfn","abcdef"};
	int ret; 

	ret = maxProduct(s, 6);
	printf("The max product is %d\n", ret);
}
