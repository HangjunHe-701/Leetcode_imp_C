#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


int strStr(char *s, char *niddle)
{
	char *p = s;
	char *q;
	char *tmp;

	while (*p) {
		q = niddle;
		if (*p != *q) {
			p++;
			continue;
		}

		// first char hit
		tmp = p;
		while (*q && *tmp++ == *q) {
			q++;	
		}
		if (*q == '\0') {
			// hit
			return p - s;
		}

		p ++;
	}

	return -1;
}

int strStr2(char *s, char *niddle)
{
	int i,j;
	int lenS = strlen(s);
	int lenN = strlen(niddle);

	for (i = 0; i < lenS-lenN; i++) {

		for (j = 0; j < lenN; j++) {
			if (s[i+j] != niddle[j]) {
				break;
			}
		}

		if (j == strlen(niddle))
			return i;
	}

	return -1;
}

int main(int argc, char **argv)
{
	char array[] = "hello";
	char niddle[] = "ll";
	//char array[] = "aaaaaaa";
	//char niddle[] = "aab";

	printf("%s strStr %s start %d\n", array, niddle, strStr2(array, niddle));
}
