#ifndef __STACK_H_
#define __STACK_H_

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
typedef struct
{
	int data[MAXSIZE];
	int top;
}STACK;


STACK *stack_create();
void stack_create2(STACK **ptr);
int stack_isempty(STACK *ptr);
int stack_isfull(STACK *ptr);
int stack_push(STACK *ptr, const int *x);
int stack_pop(STACK *ptr, int *x);
int stack_top(STACK *ptr,int *x) ; //取栈顶元素查看,不出栈
void stack_display(STACK *ptr);
void stack_destroy(STACK *ptr);

#endif
