#include <stdlib.h>
#include <stdio.h>

typedef enum {false=0, true=1} bool;

/* set n bit from start on reg */
int setbit(int reg, int start, int n)
{
	for (int i = start; i < start + n; i ++) {
		reg |= 1 << (i);
	}

	return reg;
}


// 判断系统的大小端
bool is_little_endian () 
{
	typedef union  {
		int    i;
		char c;
	} u;

	u u1;
	u1.i = 1;

	if (u1.c == 1) return true;
	else return false;
}
bool is_little_endian2 () 
{

	int    i = 1;
	char *c;

	c = (char *)&i;

	if (*c == 1) return true;
	else return false;
}


int main ()
{
	int s[] = {1, 2, 3, 4, 4, 5, 5, 6, 7, 8};
	int hit, k;
	
	int a,b;
	a=a+b;
	b=a-b;	 // b=((a+b)-b)=a
	a=a-b;	 // a=((a+b)-a)=b
	
	a=a^b;
	b=a^b;	  //b= (a^b)^b=a
	a=a^b;	  //a= (a^b)^a=b

	printf ("My machine is little endian: %s", is_little_endian()? "TRUE":"FALSE");

	return 0;
}


