#include "stack.h"


STACK *stack_create()
{
	STACK *new;

	new = malloc(sizeof(*new));
	if(new == NULL)
		return NULL;
	new->top = -1;
	return new;
}

void stack_create2(STACK **ptr)
{

	*ptr = malloc(sizeof(STACK));
	if(*ptr == NULL)
		return ;

	(*ptr)->top = -1;
	return ;
}

int stack_isempty(STACK *ptr)
{
	if(ptr->top == -1)
		return 1;
	return 0;

}
int stack_isfull(STACK *ptr)
{
	if(ptr->top == MAXSIZE-1)
		return 1;
	return 0;
}

int stack_push(STACK *ptr, const int *x)
{
	if(stack_isfull(ptr))
		return -1;
	
	ptr->data[++ptr->top] = *x;
	return 0;
}

int stack_pop(STACK *ptr, int *x)
{
	if(stack_isempty(ptr))
		return -1;
	*x = ptr->data[ptr->top--];
	return 0;
}

int stack_top(STACK *ptr,int *x)  //取栈顶元素查看,不出栈
{
	if(stack_isempty(ptr))
		return -1;
	*x = ptr->data[ptr->top];
	return 0;
}

void stack_display(STACK *ptr)
{
	int i;
	if(stack_isempty(ptr))
	    return ;
	for(i = 0 ; i <= ptr->top ; i++)
		printf("%d ",ptr->data[i]);
	printf("\n");
}

void stack_destroy(STACK *ptr)
{
	free(ptr);
	ptr = NULL;
}
