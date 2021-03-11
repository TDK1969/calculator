#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char equal[100];
char var_name[30][100];
double var_value[30];
int var_num;

double divide(int start, int end) {
    int isbrackets = 0;
    int brackets = 0;
    //遍历查找操作符号
    int i = start;
    //加减
    for (i = start; i <= end; i++) {
        //忽略括号
        if (equal[i] == '(') {
            brackets++;
        }
        if (equal[i] == ')') {
            brackets--;
        }
        if (brackets == 0 ) {
            if (equal[i] == '+') {
                return divide(start, i - 1) + divide(i + 1, end);
            } else if (equal[i] == '-' && i - 1 >= start) {
                return divide(start, i - 1) - divide(i + 1, end);
            }
        }
    }
    //乘除
    brackets = 0;
    for (i = start; i <= end; i++) {
        //忽略括号
        
        if (equal[i] == '(') {
            isbrackets = 1;
            brackets++;
        }
        if (equal[i] == ')') {
            brackets--;
        }
        if (brackets == 0) {
            if (equal[i] == '*') {
                return divide(start, i - 1) * divide(i + 1, end);
            } else if (equal[i] == '/') {
                return divide(start, i - 1) / divide(i + 1, end);
            }
        }
    }
    //去括号
    if (isbrackets) {
        return divide(start + 1, end - 1);
    }
    //数字或变量
    //暂不处理变量
    return atof(equal + start);
}

int main()
{
    int flag = 1;
    while (flag) {
        gets(equal);
        int len = strlen(equal);
        if (equal[len - 1] == '.') {
            flag = 0;
        }
        //去括号
        int x = 0, y = 0;
        for (y; y < len - 1; y++) {
            if (equal[y] != ' ') {
                equal[x++] = equal[y];
            }
        }
        int j = 0;
        for (j; j < x; j++) {
            if (equal[j] != '=') {
                var_name[var_num][j] = equal[j];
            } else {
                break;
            }
        }
        var_value[var_num] = divide(j + 1, x - 1);
        printf("%s = %lf\n", var_name[var_num], var_value[var_num]);
        var_num++;
    }
    
    
    return 0;
}