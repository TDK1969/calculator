#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char equal[100];
char var_name[30][100];
char keyword[3][10] = {
    "int","float", "write"
};
char temp_name[100];
double var_value[30];
int isint[30];
int isassign[30];
int var_num = -1;

double divide(int start, int end, int *errorno);
int judge_input();
int assignment(int len);
int float_declare(int len);
int int_declare(int len);
int write(int len);
void judge_error(int line, int errorno);
int judge_type(int type, int len);

double divide(int start, int end, int *errorno) {
    //表达式错误
    if (start > end) {
        *errorno = 1;
        return 1;
    }

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
        if (brackets == 0) {
            if (equal[i] == '+') {
                return divide(start, i - 1, errorno) + divide(i + 1, end, errorno);
            } else if (equal[i] == '-' && i - 1 >= start) {
                return divide(start, i - 1, errorno) - divide(i + 1, end, errorno);
            }
        }
    }
    //括号不闭合
    if (brackets != 0) {
        *errorno = 1;
        return 1;
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
                return divide(start, i - 1, errorno) * divide(i + 1, end, errorno);
            } else if (equal[i] == '/') {
                double front = divide(start, i - 1, errorno);
                double back = divide(i + 1, end, errorno);
                if (back == 0.0) {
                    *errorno = 4;
                    return 1;
                } else {
                    return front / back;
                }
            }
        }
    }
    //去括号
    if (isbrackets) {
        return divide(start + 1, end - 1, errorno);
    }

    //数字或变量,此时已经是最小单位
    double value = atof(equal + start);
    if (value == 0 && isalpha(equal[start])) {
        //判断为变量
        memset(temp_name, 0, sizeof(temp_name));
        for (int i = start; i <= end; i++) {
            temp_name[i - start] = equal[i];
        }

        for (int i = 0; i <= var_num; i++) {
            if (strcmp(var_name[i], temp_name) == 0) {
                //找到已声明的变量
                if (isassign[i] == 0) {
                    *errorno = 6;
                    return 1;
                }
                return var_value[i];
            }
        }
    } else {
        //否则为数字
        return value;
    }
}

int judge_input() {
    //判断语句类型
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
    //处理去括号后的字符串
    memset(equal + x, 0, sizeof(equal) - x);
    int j = 0;
    memset(temp_name, 0, sizeof(temp_name));
    for (j; j < x; j++) {
        if (equal[j] != '=') {
            temp_name[j] = equal[j];
        } else {
            break;
        }
    }
    int var_no = 0;
    for (var_no; var_no <= var_num; var_no++) {
        if (strcmp(var_name[var_no], temp_name) == 0) {
            //如果变量名已经声明，则进行赋值
            int errorno = 0;
            double value = divide(j + 1, x - 1, &errorno);
            if (errorno != 0) {
                return errorno;
            }
            if (isint[var_no] == 1) {
                var_value[var_no] = (int)value;
            } else {
                var_value[var_no] = value;
            }
            isassign[var_no] = 1;
            //printf("调试信息：%s = %lf\n", var_name[var_no], var_value[var_no]);
            return 0;
        }
    }
    return 2;  
}

int float_declare(int len) {
    //实数型变量声明
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

    for (int i = 0; i < 3; i++) {
        if (strcmp(temp_name, keyword[i]) == 0) {
            return 7;
        }
    }

    for (int i = 0; i <= var_num; i++) {
        if (strcmp(var_name[i], temp_name) == 0) {
            return 5;
        }
    }

    var_num++;
    strcpy(var_name[var_num], temp_name);
    return 0;
}

int int_declare(int len) {
    //整型变量声明
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

    for (int i = 0; i < 3; i++) {
        if (strcmp(temp_name, keyword[i]) == 0) {
            return 7;
        }
    }

    for (int i = 0; i <= var_num; i++) {
        if (strcmp(var_name[i], temp_name) == 0) {
            return 5;
        }
    }

    var_num++;
    isint[var_num] = 1;
    strcpy(var_name[var_num], temp_name);
    return 0;
}

int write(int len) {
    //对变量的值进行输出
    memset(temp_name, 0, sizeof(temp_name));
    for (int i = 6; i < len - 2; i++) {
        temp_name[i - 6] = equal[i];
    }

    for (int i = 0; i <= var_num; i++) {
        if (strcmp(var_name[i], temp_name) == 0) {
            if (isassign[i] == 0) {
                return 6;
            }
            if (isint[i] == 1) {
                printf("%s = %d\n", temp_name, (int)var_value[i]);
                return 0;
            } else {
                printf("%s = %lf\n", temp_name, var_value[i]);
                return 0;
            }
        }
    }
    return 2;
}

int judge_type(int type, int len) {
    if (type == 1) {
        return float_declare(len);
    } else if (type == 2) {
        return int_declare(len);
    } else if (type == 3) {
        return write(len);
    } else {
        return assignment(len);
    }
}

void judge_error(int line, int errorno) {
    //对错误类型进行判断
    if (errorno == 1) {
        printf("Error(line %d):wrong expression.\n", line);
    } else if (errorno == 2) {
        printf("Error(line %d):undefined identifier.\n", line);
    } else if (errorno == 3) {
        printf("Error(line %d):invalid identifier.\n", line);
    } else if (errorno == 4) {
        printf("Error(line %d):divided by zero.\n", line);
    } else if (errorno == 5) {
        printf("Error(line %d):repeated definition.\n", line);
    } else if (errorno == 6) {
        printf("Error(line %d):unassigned identifier.\n", line);
    } else if (errorno == 7) {
        printf("Error(line %d):identifier conflict with keywords.\n", line);
    }
}

int main(int argc, char* argv[])
{
    //如果参数数量错误则报错，程序结束
    if (argc != 3) {
        printf("Lack of parameter!\n");
        return 0;
    }

    //输入输出重定向至文件
    FILE* fp = freopen(argv[1], "r", stdin);
    //如果输入文件不存在，则报错，程序结束
    if (!fp) {
        printf("file %s does not exist.\n", argv[1]);
    }
    freopen(argv[2], "w", stdout);

    
    
    
    int flag = 1;
    int line = 1;

    while (flag) {
        //如果用户忘了在最后一个语句输入'.'，则通过检测文件结尾退出
        
        if (feof(fp) != 0) {
            break;
        }
        
        //对语句读入并进行处理
        memset(equal, 0, sizeof(equal));
        gets(equal);
        int len = strlen(equal);
        if (equal[len - 1] != '.' && equal[len - 1] != ';') {
            printf("Error(line %d):lack ';' or '.' at the end.\n", line);
            line++;
            continue;
        }
        if (equal[len - 1] == '.') {
            flag = 0;
        }

        //进行语句类型判断：声明、赋值和输出
        int type = judge_input(equal);
        int errorno = 0;
        errorno = judge_type(type, len);
        /*
        //取消注释则遇到错误停止
        if (errorno != 0) {
            flag = 0;
        }
        */
        judge_error(line, errorno);

        line++;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}