// build with char_stack.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "char_stack.h"


int validParentness(char *s)
{
	stack * stack;
	int i = 0, ret = 0;
	char temp;

	if (strlen(s) == 0) return 0;

	stack = StackCreate();	

	while (s[i]) {
		if (s[i] == '{' || s[i] == '(' || s[i] == '[')
			StackInput(stack, s[i]);
		else {
			temp = StackOutput(stack);
			if ((s[i] == '}' && temp != '{') ||
				(s[i] == ')' && temp != '(') ||
				(s[i] == ']' && temp != '[')) { 
				ret = -1;
				goto out ;
			}	
		}	
		i ++;
	}
	if (StackOutput(stack) != 0)
		ret = -1;

out:
	StackFree(stack);
	return ret;
}

int main(int argc, char **argv)
{
    //char array[] = "{}";
    //char array[] = "()[]{}{}";
    char array[] = "([)](";

    int result = validParentness(array);
    printf("string %s is %s parentness\n", array, result==0 ? "valid": "invalid");
}
