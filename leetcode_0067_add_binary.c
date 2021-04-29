#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


char * addBinary(char *s, char *t)
{
	char *ret;
	int lenS = strlen(s);
	int lenT = strlen(t);
	int longer = (lenT > lenS) ? (lenT) : (lenS);
	int lenR = longer + 1;
	int *intR; 
	int i, j, k = lenR-1;
	int head_zero = 0;

	ret = malloc(lenR + 1);
	
	intR = malloc(sizeof(int) * lenR);
	memset(intR, 0, sizeof(int) * (lenR));

	for (i = lenS - 1, j = lenT - 1; i >= 0 || j >= 0; i--, j--, k--) {

		if (i >= 0 && j >= 0) {
			intR[k] += s[i] - '0' + t[j] - '0';
		} else if (i >= 0) {
			intR[k] += s[i] - '0';
		} else {
			intR[k] += t[j] - '0';
		}

		if (intR[k] >= 2) {
			intR[k-1] = intR[k] / 2;
			intR[k] %= 2;
		}
	}

	if (intR[0] == 0) head_zero = 1;

	for (i = 0; i < lenR - head_zero; i++) {
		ret[i] = (char)intR[i+head_zero] + '0';
	}
	ret[i] = '\0';

	free(intR);
	return ret;
}


int main(int argc, char **argv)
{
	//char s[] = "1010";
	//char t[] = "1011";
	char s[] = "11";
	char t[] = "1";
	char * ret = addBinary(s, t);

	printf("%s * %s = %s\n", s, t, ret);
	free (ret);
}
