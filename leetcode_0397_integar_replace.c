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

int integarReplace(int n)
{
	int count = 0; 

	while (n != 1) {
		// even
		if ((n & 1) == 0)
			n /= 2;
		else {
			// (n + 1) % 4 == 0
			// 3 is special 
			if ((n + 1) % 4 == 0 && n != 3) {
				n ++; 
			} else {
				n --; 
			}
		}
		count++;
	}

	return count;
}

int main(int argc, char **argv)
{
	int n = 15;
	int ret; 

	ret = integarReplace(n);
	printf("The interger %d replace count %d\n", n, ret);
}
