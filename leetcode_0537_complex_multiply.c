#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h" 

char* complexNumberMultiply(char* s, char *t, char *buf)
{
	int realS, imagS, realT, imagT, realR, imagR;
	char *p;
	
	realS = atoi(s);
	p = strchr(s, '+');
	p++;
	imagS = atoi(p);

	realT = atoi(t);
	p = strchr(t, '+');
	p++;
	imagT = atoi(p);
		
	realR = realS * realT - imagT * imagT;
	imagR = realS * imagT + realT * imagT;

	sprintf(buf, "%d+%di", realR, imagR);
	return buf;
}

int main(int argc, char **argv)
{
    char array[] = "1+-1i";
    char array2[] = "-1+-1i";
	char buf[16];

    printf("The %s * %s = %s\n", array, array2, complexNumberMultiply(array, array, buf));
}


