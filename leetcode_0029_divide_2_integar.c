#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <climits>
using namespace std;

int divideTwoIntegars(int dividend, int divisor)
{
	int result = 0,sign = -1;
	int dvd, dvs;

	if (dividend == (2<<30) && divisor == -1) {
		return 0x7FFFFFFF;   
	}

	if (dividend > 0 && divisor > 0 || dividend < 0 && divisor < 0) {
		sign = 1;
	}

	dvd = abs(dividend);
	dvs = abs(divisor);
	while (dvd >= dvs) {
		int temp = dvs;
		int m = 1;
		// pow 2
		while (temp<<1 <= dvd) {
			temp <<= 1;
			m <<= 1;
		}
		dvd -= temp;
		result += m;
	}
	return sign * result;
}

int main(int argc, char **argv)
{
	//int dividend=18, divisor=3;
	int dividend=-2147483648, divisor=-1;

	cout << INT_MAX << ' ' << 0x7fffffff << endl;
	int ret = divideTwoIntegars(dividend, divisor);
	printf ("%d / %d = %d\n", dividend, divisor, ret);
}
