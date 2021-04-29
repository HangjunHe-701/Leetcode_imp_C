#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

static int ret_index = 0;
char ** wordSubsets(char *a[], int aSize, char *b[], int bsize)
{
	char **ret;
	int i,j;
	int map[26];
	bool good = false;
	int count[26] = {0};

	ret = malloc(aSize * sizeof(int*));

	for (i = 0; i < bsize; i++) {

		memset(map, 0, sizeof(int) * 26);
		for (j = 0; j < strlen(b[i]); j++) {
			map[b[i][j] - 'a']++;
		}

		for (j = 0; j < 26; j++) {
			if (map[j] > count[j]) {
				count[j] = map[j];
			}	
		}
	}	

	for (i = 0; i < aSize; i++) {

		memset(map, 0, sizeof(int) * 26);
		for (j = 0; j < strlen(a[i]); j++) {
			map[a[i][j] - 'a']++;
		}

		good = true;
		for (j = 0; j < 26; j++) {
			if (map[j] < count[j]) {
				good = false;
			}	
		}
		if (good) {
			ret[ret_index++] = strdup(a[i]);
			// failed
		}
	}	

	return ret;
}

int main(int argc, char **argv)
{
	char *s[] = {"amazon","apple","facebook","google","leetcode"};
	char *t[] = {"e","oo"};
	
	char ** ret = wordSubsets(s, 5, t, 2);

	for (int i = 0; i < ret_index; i++)
		printf("%d %s\n", i+1, ret[i]);
}
