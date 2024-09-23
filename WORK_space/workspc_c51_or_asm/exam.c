#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100



typedef struct {
    double data[MAXLEN];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, double val) {
    s->data[++(s->top)] = val;
}

double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return 0;
}

double top(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return 0;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

double evaluate(char* expression) {
    int i;
    Stack values, ops;
    initStack(&values);
    initStack(&ops);

    for (i = 0; i < strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            double val = 0;
            while (i < strlen(expression) && ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.')) {
                if (expression[i] == '.') {
                    double fraction = 1;
                    i++;
                    while (i < strlen(expression) && (expression[i] >= '0' && expression[i] <= '9')) {
                        fraction /= 10;
                        val += (expression[i] - '0') * fraction;
                        i++;
                    }
                } else {
                    val = (val * 10) + (expression[i] - '0');
                    i++;
                }
            }
            i--;
            push(&values, val);
        } else if (expression[i] == '(') {
            push(&ops, expression[i]);
        } else if (expression[i] == ')') {
            while (!isEmpty(&ops) && top(&ops) != '(') {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            if (!isEmpty(&ops)) {
                pop(&ops);
            }
        } else {
            while (!isEmpty(&ops) && precedence(top(&ops)) >= precedence(expression[i])) {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            push(&ops, expression[i]);
        }
    }

    while (!isEmpty(&ops)) {
        double val2 = pop(&values);
        double val1 = pop(&values);
        char op = pop(&ops);
        push(&values, applyOp(val1, val2, op));
    }

    return pop(&values);
}

int main() {
    // char expression[MAXLEN];
    // printf("Enter a mathematical expression: ");
    // fgets(expression, MAXLEN, stdin);
    // expression[strcspn(expression, "\n")] = '\0';  // Remove trailing newline

	char expression[MAXLEN];
	memset(expression , 0 ,sizeof(expression));
	expression[0] = '1';
	expression[1] = '+';
	expression[2] = '(';
	expression[3] = '3';
	expression[4] = '+';
	expression[5] = '4';
	expression[6] = ')';
	expression[7] = '*';
	expression[8] = '2';
    printf("The result is: %lf\n", evaluate(expression));
	double result = evaluate(expression);
	printf("%d" , (int)result);
    return 0;
}
