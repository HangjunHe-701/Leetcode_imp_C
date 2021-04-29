#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// DFS (deep forward searching) recursive
static int ret_index = 0;
void findGenerateParentness(int lindex, int rindex, char ** ret, char *tmp, int index)
{
	if (lindex == 0 && rindex == 0) {
		ret[ret_index] = strdup(tmp);
		ret_index ++;
		return;
	}

	if (lindex > 0) { 
		tmp[index] = '(';
		findGenerateParentness(lindex-1, rindex, ret, tmp, index+1);	
	}
	//  right forward steps could not faster than left's
	if (rindex > 0 && lindex < rindex) {
		tmp[index] = ')';
		findGenerateParentness(lindex, rindex-1, ret, tmp, index+1);	
	}
}

char ** generateParentness(int n)
{
	int i = 0;
	char** ret = malloc(sizeof(char *) * (1 << n));
	//int ret_index = 0;

	char *tmp = malloc(2*n+1);
	tmp[2*n] = '\0';
	
	findGenerateParentness(n, n, ret, tmp, 0);
	free(tmp);
	return ret;
}

int main(int argc, char **argv)
{
	char ** ret = NULL;

    ret = generateParentness(3);
	for (int i = 0; i < ret_index; i++) {
		printf("%d: %s\n", i+1, ret[i]);
		free(ret[i]);
	}
	free(ret);
}
