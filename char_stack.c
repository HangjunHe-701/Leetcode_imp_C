/*
 * This is only a very simple stack to store char
 */

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
	char data[100];
	int top;
	int bottom;
} stack;

//** 创建  */
stack * StackCreate(void) 
{
	stack * p = (stack*)malloc(sizeof(stack));
	if (p) {
		p->bottom = p->top = 0;
		return p;
	}
		
	return NULL;
}

//** 入栈  */
void StackInput(stack * p, char ch)
{
	p->data[p->top] = ch;
	p->top++;
	//printf("%s: %c len %d\n", __func__, ch, p->top);
	//return p;
}

//** 出栈  */
char StackOutput(stack* p)
{
	if (p->bottom != p->top){
		char ch = p->data[p->top - 1];
		p->top--;
		//printf("%s: %c len %d\n", __func__, ch, p->top);
		return ch;
	}

	return 0;
}

//** top  */
char StackGet(stack* p)
{
	if (p->bottom != p->top){
		char ch = p->data[p->top - 1];
		return ch;
	}

	return 0;
}

//** 栈length  */
int StackLength(stack * p)
{
	return p->top - p->bottom;
}

void StackFree(stack* p)
{
	free(p);
}
