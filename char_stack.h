typedef struct {
	char data[100];
	int top;
	int bottom;
} stack;

//** 创建  */
stack * StackCreate(void);
void StackInput(stack * p, char ch);
char StackOutput(stack* p);
char StackGet(stack* p);
int StackLength(stack * p);
void StackFree(stack* p);
