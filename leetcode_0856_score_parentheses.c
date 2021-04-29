#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

int scoreOfParentheses(char *s)
{
	int *ret;
	int ret_index = -1;
	int i = 0,len = strlen(s);
	int temp;

	ret = malloc(len * sizeof(int));

	for (i = 0; i < len; i++) {

		if (s[i] == '(') {
			ret_index ++;
			ret[ret_index] = -1;
			continue;
		}

		temp = 0;
		while (ret[ret_index] != -1 && ret_index > 0) {
			temp += ret[ret_index];
			ret_index --;

			printf("3 ret_index %d %d\n", ret_index, ret[ret_index]);
		}

		// -1 means '('
		ret_index --;

		if (temp) {
			ret_index ++;
			ret[ret_index] = 2 * temp;
			printf("2 ret_index %d %d\n", ret_index, ret[ret_index]);
		} else {
			ret_index ++;
			ret[ret_index] = 1;
			printf("ret_index %d\n", ret_index);
		}
	}	

	return ret[0];
}

int main(int argc, char **argv)
{
	char s[] = "(()(()))";
	int  ret = scoreOfParentheses(s);

	printf("%s score is %d\n", s, ret);

}
