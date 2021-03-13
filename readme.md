# 类型判断
+ 声明
+ 输出
+ 赋值
# 错误类型
1. 表达式错误
2. 变量未声明
3. 变量命名非法
4. 除零错误
5. 重复声明
6. 变量未赋值
7. 保留字冲突

# 测试用例
## 测试用例1：普通测试
float a;
int b;
a = (10.44*356+1.28)/2 + 1024*1.6;
b = a*2-a/2;
write(b);
write(a).

## 测试用例2：较复杂的算术表达式
float aisuhbdfw;
float uhweifn;
aisuhbdfw = (2.766-769.1/45)*(10000.2345/(2074-849.78165));
write(aisuhbdfw);
uhweifn = (aisuhbdfw+1024.4021)/(1969+1987/666);
write(uhweifn).

## 测试用例3：除零错误测试
float a;
int b;
a = 2333;
b = 1234/(a - 2333);
write(b).

## 测试用例4：表达式错误
float a;
a = (45+23)/2+;
write(a).

## 测试用例4：变量未声明
float a;
int b;
a = c/2 + b*2;
write(a).

## 测试用例5：非法变量命名
float aaosidfn7da;
int 8asiudbf;
float niqowne**h7jq.

## 测试用例6：保留字冲突
float int;
int write.
TODO:文法分析