// build with char_stack.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "char_stack.h"


int simply_path(char *s)
{
	stack * stack;
	int i = 0, ret = 0;
	char temp;

	if (strlen(s) == 0) return 0;

	printf ("string is %s\n", s);
	stack = StackCreate();	

	while (s[i]) {
#if 1
		if (s[i] == '/') {
			StackInput(stack, s[i]);
			i++;
			while (s[i] == '/') {
				i++;
				continue;
			}
			continue;
		} else 
#endif
		if  (s[i] == '.') {
			StackOutput(stack);
			if (s[i+1] == '.')
			while((temp = StackGet(stack)) != '/' && StackGet(stack) != 0) {
				StackOutput(stack);
				continue;
			}
		} else	
			StackInput(stack, s[i]);

		i ++;
	}

	if ((temp = StackOutput(stack)) != '/')
		StackInput(stack, temp);
		
	printf ("stacklength is %d\n", StackLength(stack));
	while (temp = StackOutput(stack))
		printf ("%c\n", temp);

out:
	StackFree(stack);
	return ret;
}

int main(int argc, char **argv)
{
    //char array[] = "/a//b////c/d//././/..";
    //char array[] = "/a/../../b/../c//.//";
    //char array[] = "/a/./b/../../c/";
    //char array[] = "/foo//";
	//char array[] = "/a/./b/../../c/";
	char array[] = "/home//foo/";

    int result = simply_path(array);
}
