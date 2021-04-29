#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

bool isLongPressedName(char *a, char *b)
{
	int i = 0, j = 0;

	while (i < strlen(a) && j < strlen(b)) {
		if (a[i] == b[j]) {
			j++;
			i++;
			continue;
		} else if (a[i] != b[j] && b[j] == a[i-1]) {
			j++;
			continue;
		}

		return false;
	}

	return true;
}

int main(int argc, char **argv)
{
	//char s[] = "saeed", t[] = "ssaaedd";
	char s[] = "alex",  t[] = "aaleex";
	
	printf("%s vs %s longPressedName %d\n", s, t, isLongPressedName(s, t));
}
