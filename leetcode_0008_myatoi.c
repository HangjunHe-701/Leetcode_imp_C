#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Offer 67
// 关键每次的和乘10实现10的指数
enum {valid = 0, inValid};
int gValidStatus = inValid;
int my_atoi(char *ptr)
{
	char *p;
	int neg = 0;
	int i;
	//int maxInt;
	unsigned int maxInt;
	int64_t n = 0;

	if (ptr == NULL) {
		return 0;
	}

	p = ptr;

	while(*p == ' ') p++;

	maxInt = 1<<31; //0x7fffffff;
	if (*p == '-') {
		neg = 1;
		p++;
	} else
		maxInt --;

	printf("max 0x%x\n", maxInt);

	if (*p == '0') {
		return 0;
	}
	while (*p <= '9' && *p >= '0') {
		n = n * 10 + (*p - '0');
		if (n > maxInt) {
			n = maxInt;
			break;
		}
		p ++;
	}

	if (*p == '0') {
		gValidStatus = valid;
	}
	if (neg) n = -n;
	
	return n;
}

int main ()
{
	printf ("\nmy_atoi = %d %d %d %d 1=%d\n",  my_atoi("1234hel"), my_atoi("   -123"), my_atoi("-91283472332"), my_atoi("91283472332"), '1');
	printf ("\natoi = %d %d %d %d 1=%d\n",  atoi("1234hel"), atoi("   -123"), atoi("-91283472332"), atoi("91283472332"), '1');

	return 0;
}


