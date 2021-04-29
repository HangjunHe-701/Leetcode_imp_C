#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static char hex[9] = {0};
char* toHex(int n)
{
	int count = 0; 
	int tmp; 
	unsigned int m = n;
	char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	if (n == 0) return 0;
	if (n < 0) {
		// 将num按位取反，然后加1，得到补码
		//m = n + 0xffffffff + 1;
		m = (0xffffffff ^ (-n)) + 1;
	}

	while (m != 0) {
		hex[count++] = map[m % 16];
		m /= 16;
	}

	// reverse
	for (int i = 0; i < count/2; i++) {
		tmp = hex[i];
		hex[i] = hex[count - i -1];
		hex[count - i -1] = tmp;
	}
	hex[count] = '\0';

	return hex;
}

int main(int argc, char **argv)
{
	int n = -1;
	int ret; 

	printf("The interger 0x%x to hex %s\n", n, toHex(n));
}
