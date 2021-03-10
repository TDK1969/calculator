#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//实现基础的计算功能

typedef struct stack_elem {
    int type;
    double value;
    char operator;
    char name[20];
} stack_elem;

stack_elem transform_stack[100];
int transform_top = -1;
stack_elem calculate_stack[100];
int calculate_top = -1;
char operator_stack[100];
int operator_top = -1;

double cal_equal() {
    transform_top = calculate_top = operator_top = -1;
    char str[30];
    scanf("%s", str);
    int endflag = 1;
    
    while (endflag) {
        if ((str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/') && str[1] == '\0') {
            if (str[0] == '+' || str[0] == '-') {
                while (operator_top >= 0 && \
                (operator_stack[operator_top] != '*' && operator_stack[operator_top] != '/')) {
                    transform_top++;
                    transform_stack[transform_top].type = 2;
                    transform_stack[transform_top].operator = operator_stack[operator_top--];
                }
            }
            if (str[0] == ')')
            operator_stack[++operator_top] = str[0];
        } else if (str[0] == '('){

        }
    }
}
int main()
{
    int flag = 1;
    char equal[100];
    
    while(flag) {
        transform_top = calculate_top = operator_top = -1;
        char str[30];

    }
    

    return 0;
}
