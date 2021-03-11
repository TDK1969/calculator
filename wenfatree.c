#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char equal[100];
char var_name[30][100];
char temp_name[100];
double var_value[30];
int isint[30];
int var_num = -1;

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

int judge_input() {
    if (equal[0] == 'f' && equal[1] == 'l' && equal[2] == 'o' && equal[3] == 'a'\
        && equal[4] == 't' && equal[5] == ' ') {
        //float变量声明
        return 1;
    } else if (equal[0] == 'w' && equal[1] == 'r' && equal[2] == 'i' && equal[3] == 't'\
        && equal[4] == 'e' && equal[5] == '(') {
        //输出指令
        return 3;
    } else if (equal[0] == 'i' && equal[1] == 'n' && equal[2] == 't' && equal[3] == ' ') {
        //int变量声明
        return 2;
    } else {
        //赋值语句
        return 4;
    }
}

int assignment(int len) {
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
    printf("调试信息：%s = %lf\n", var_name[var_num], var_value[var_num]);
    var_num++;    
}

int float_declare(int len) {
    if (isdigit(equal[6])) {
        return 3;
    }
    memset(temp_name, 0, sizeof(temp_name));
    for (int i = 6; i < len - 1; i++) {
        if (!isalnum(equal[i])) {
            return 3;
        }
        temp_name[i - 6] = equal[i];
    }

    for (int i = 0; i <= var_num; i++) {
        if (strcmp(var_name[i], temp_name) == 0) {
            return 5;
        }
    }

    var_num++;
    strcpy(var_name[var_num], temp_name);
}

int int_declare(int len) {
    if (isdigit(equal[4])) {
        return 3;
    }
    memset(temp_name, 0, sizeof(temp_name));
    for (int i = 4; i < len - 1; i++) {
        if (!isalnum(equal[i])) {
            return 3;
        }
        temp_name[i - 4] = equal[i];
    }

    for (int i = 0; i <= var_num; i++) {
        if (strcmp(var_name[i], temp_name) == 0) {
            return 5;
        }
    }

    var_num++;
    isint[var_num] = 1;
    strcpy(var_name[var_num], temp_name);
}

int write(int len) {
    
}

int main()
{
    int flag = 1;
    int line = 1;
    while (flag) {
        gets(equal);
        int len = strlen(equal);
        if (equal[len - 1] == '.') {
            flag = 0;
        }
        //进行语句类型判断：声明、赋值和输出
        int type = judge_input(equal);
        int errorno = 0;
        if (type == 1) {
            errorno = float_declare(len);
        } else if (type == 2) {
            errorno = int_declare(len);
        } else if (type == 3) {
            errorno = write(len);
        } else {
            errorno = assignment(len);
        }
        line++;
    }
    return 0;
}