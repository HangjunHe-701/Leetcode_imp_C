#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


/*
 * x & x - 1 can remove one 1 bit so count[x] = count[x & x - 1] + 1
 */
int * countBits(int n)
{
	int max = 0; 
	int i, j;
	int *vector;

	vector = malloc(sizeof(int)*(n+1));
	// failed not considered
    memset(vector, 0, sizeof(int)*(n+1));	

	vector[0] = 0;
	for (i = 1; i <= n; i++) {
		vector[i] = vector[i & i-1] + 1;
	}

	return vector;
}

int main(int argc, char **argv)
{
	char *s[] = {"abcw","baz","foo","bar","xtfn","abcdef"};
	int * ret; 
	int n = 6;

	ret = countBits(n);
	printf("The countBits\n");
	for (int i= 0; i <= n; i++) {
		printf("%d\t", ret[i]);
	}
	printf("\n");
	free(ret);
}
