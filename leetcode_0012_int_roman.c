#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


char* int_roman(int num)
{
	int i = 0;
	char * result, *p;
	int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

	result = (char *)malloc(32);
    if (num == 0) { 
		result[0] = '\0';
		return result;
	}

	p = result;
	while (num != 0) {
		while (values[i] > num) {
			i++;
		}
		num -= values[i];
		p += sprintf(p, "%s", symbols[i]);
	}
	return result;
}

int main(int argc, char **argv)
{
	int num = 3999;
    char* result = int_roman(num);
    printf("integar %d to roman %s\n", num, result);
	free (result);
}

