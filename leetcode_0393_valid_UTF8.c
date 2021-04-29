#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
   Char. number range  |        UTF-8 octet sequence
      (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

typedef enum {false = 0, true = 1} bool;
bool validUtf8(int *s, int n)
{
	int count = 0; 

	for (int i = 0; i < n; i++) {
		if (count == 0) {
			if (s[i] > 248) // 11111000
				return false;
			else if (s[i] > 240) // 11110000
				count = 3;
			else if (s[i] > 224) // 11100000
				count = 2;
			else if (s[i] > 192) // 11000000
				count = 1;
			else if (s[i] > 127) // 01111111
				return false;
			// else good
		} else {
			if (s[i] <= 127 || s[i] >= 192)
				return false;
			count --;
		}
	}

	return (count == 0);
}

int main(int argc, char **argv)
{
	int s[] = {197, 130, 1};
	bool ret; 

	ret = validUtf8(s, 3);
	printf("The interger array is UTF-8 %d\n", ret);
}
