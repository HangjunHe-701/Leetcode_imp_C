#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

int firstUniqueChar(char* s)
{
	int i;
	int ret = -1;
	int map[26] = {0};

	for (i = 0; i < strlen(s); i++) {
		map[s[i] - 'a'] ++;
	}

	for (i = 0; i < strlen(s); i++) {
		if (map[s[i] - 'a'] == 1) return i; 
	}

	return ret;
}

int main(int argc, char **argv)
{
    char array[] = "loveleetcode";

    printf("The \"%s\" first unique char index %d\n", array, firstUniqueChar(array));
}


