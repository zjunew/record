#include <stdlib.h>
#include <string.h>

unsigned char nums[20];
unsigned char re[8];
unsigned char count = 0;

typedef struct node {
    unsigned char date;
    char opt;
    struct node* pre;
}* pnode, node;

typedef struct stack {
    pnode bottom;   //指向底部
    pnode top;  //指向头部
}* pstack, stack;

pstack create_stack(void) {
    pstack s = (pstack)malloc(sizeof(stack));
    s->bottom = s->top = (pnode)malloc(sizeof(node));
    return s;
}

void push(pstack s, char date) {
    pnode t = (pnode)malloc(sizeof(node));
    t->pre = s->top;
    t->date = date;
    s->top = t;
}

void pop(pstack s) {
		pnode t = s->top;
    if (s->top == s->bottom) 
		{
        return ;
    }
    s->top = s->top->pre;
    free(t);
}

unsigned char empty(pstack s) {
    if (s->top == s->bottom) {
        return 1;
    }
    else {
        return 0;
    }
}

unsigned char top(pstack s) {
    return s->top->date;
}

void push_num(pstack s, unsigned char date) {
    pnode t = (pnode)malloc(sizeof(node));
    t->pre = s->top;
    t->date = date;
    s->top = t;
}


unsigned char cal()
{
    unsigned char mysize = 0;
    unsigned char sum = 0, ans = 0;
    
    char str[20], suffix[20];
    unsigned char opt[20];
    unsigned char len = count, p = 0, flag = 1 , i , t1;
   
		pstack number_stack = create_stack();
		pstack s_opt = create_stack();
    pstack s_num = create_stack();
  	opt['+'] = opt['-'] = 1;
    opt['*'] = opt['/'] = 2;
    opt['('] = opt[')'] = 0;
	  memset(opt, 0, sizeof(opt));
    strncpy(str , (char*)nums , count);
    for (i = 0; i < len; i++) {
        if (str[i] <= '9' && str[i] >= '0') {
            suffix[p++] = str[i];
            if (i+1 < len && str[i+1] <= '9' && str[i+1] >= '0');
            else    suffix[p++] = ' ';
            flag = 0;
            continue;
        }
        else {
            flag++;
        }
        if (str[i] == '(') {
            push(s_opt, str[i]);
        }
        else if (str[i] == ')') {
            while(top(s_opt) != '(') {
                suffix[p++] = top(s_opt);
                pop(s_opt);
            }
            pop(s_opt);
        }
        else if (empty(s_opt) && str[i] != ' ') {
            push(s_opt, str[i]);
        }
        else {
            while(!empty(s_opt) && opt[str[i]] <= opt[top(s_opt)]) {
                suffix[p++] = top(s_opt);
                pop(s_opt);
            }
            push(s_opt, str[i]);
        }
    }
    while(!empty(s_opt)) {
        suffix[p++] = top(s_opt);
        pop(s_opt);
    }
        
    flag = 0;
    sum = 0, ans = 0;
    for (i = 0; i < p; i++) {
        if (suffix[i] <= '9' && suffix[i] >= '0') {
            sum = sum*10 + (suffix[i]-'0');
            flag = 1;
        }
        else {
            if (flag == 1) {
                push(number_stack, sum);
                sum = 0;
                flag = 0;
            }
            if (suffix[i] == '+' || suffix[i] == '-' || suffix[i] == '*' || suffix[i] == '/') {
                t1 = number_stack->top->date;
                pop(number_stack);
                if (suffix[i] == '+') {
                    number_stack->top->date += t1;
                }
                else if (suffix[i] == '-') {
                    number_stack->top->date -= t1;
                }
                else if (suffix[i] == '*') {
                    number_stack->top->date *= t1;
                }
                else if (suffix[i] == '/') {
                    number_stack->top->date /= t1;
                }
            }
        }
    }
    sum = number_stack->top->date;
    mysize = 0;
    while(sum>0)
    {
        i = sum %10;
        re[mysize] = i ;
        mysize ++;
        sum = sum / 10;
    }
    return mysize;
}