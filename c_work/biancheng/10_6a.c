// ============================================================
// 第10章 第6题：逆波兰表达式（RPN）求值
// 题目：
//   操作数是个位整数，运算符 + - * / 和 =。
//   遇到 = 显示栈顶并清空栈，提示输入新表达式。
//   输入非操作数非运算符字符则退出。
//   栈上溢显示 "Expression is too complex" 并终止。
//   栈下溢显示 "Not enough operands in expression" 并终止。
// ============================================================

// ! 你的原始代码（整段注释，你的笔记用 / 保留，批改见下方）：
/*
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define STACK_SIZE 100
char stack[STACK_SIZE];
int top = 0;
int sum(int pop1, int pop2, char c);
void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}
void stack_overflow(void)
{
    printf("Stack overflow\n");
    exit(EXIT_FAILURE);
}
// * 栈下溢：出现在右括号多余时。
// * 题目说“如果曾经调用过 stack_underflow 函数，那么不匹配”，
// * 这里直接输出不匹配信息并终止，效果一致。
void stack_underflow(void)
{
    printf("Parentheses/braces are not nested properly\n");
    exit(EXIT_FAILURE);
}
void push(char c)
{
    if (is_full()) stack_overflow();
    else stack[top++] = c;
}
int pop(char c)
{
    int pop1, pop2;
    if (is_empty()) stack_underflow();
    else {pop1 = stack[--top], pop2 = stack[--top];}
    return sum(pop1, pop2, c);
}
int sum(int pop1, int pop2, char c)
{
    static int sum = 0;
    pop1 -= '0', pop2 -= '0';
    switch (c) {
        case '+': push(pop2 + pop1 + '0'); sum = pop2 + pop1; break;
        case '-': push(pop2 - pop1 + '0'); sum = pop2 - pop1; break;
        case '*': push(pop2 * pop1 + '0'); sum = pop2 * pop1; break;
        case '/': push(pop2 / pop1 + '0'); sum = pop2 / pop1; break;
        default: break;
    }
    return sum;

}
int main(void)
{
    char ch;
    int sum;
    for (;;) {
    printf("Enter an RPN expreddion: ");
    while ((ch = getchar()) != EOF && ch != '=') {
        if (ch == ' ' || ch == '\n') continue;
        if (ch >= '0' && ch <= '9') push(ch);
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') sum = pop(ch);
        else exit(0);

    }
    printf("Value of expression: %d\n", sum);
}


    return 0;
}
*/

// ============================================================
// * 批改：
// ============================================================
// ❌ 1. 栈用 char 存操作数和中间结果，根本错误。
//    操作数虽然是个位数字，但中间结果可能超过 9。
//    例如 5 8 *，结果 40，push(40 + '0') 存进去的是字符 'X'，
//    下次弹出减 '0' 得到 88，后续计算全错。
//    栈应该用 int，push/pop 都操作 int。
//
// ❌ 2. pop 函数设计混乱。
//    既弹栈、又调用 sum、又返回 sum，职责不清。
//    应该 pop 只负责弹出一个 int，运算符计算在 main 或单独函数里做。
//
// ❌ 3. sum 函数用 static 变量记录结果，没必要且易错。
//    每次运算的结果直接 push 回栈即可，最后从栈顶取值。
//
// ❌ 4. stack_underflow 的提示语是括号匹配题留下的，
//    本题应为 "Not enough operands in expression"。
//
// ❌ 5. stack_overflow 的提示语应为
//    "Expression is too complex"。
//
// ❌ 6. 遇到 '=' 时没有从栈顶取值，而是用 sum 变量。
//    sum 只记录最后一次二元运算结果。
//    如果表达式只有一个操作数（如 "5 ="），
//    sum 未初始化，输出错误。
//    正确做法：遇 '=' 时弹出栈顶作为结果，然后清空栈。
//
// ❌ 7. 遇 '=' 后没有清空栈，下一轮表达式会受上一轮残留影响。
//
// ❌ 8. 变量 sum 与函数 sum 同名，局部变量遮蔽函数名，
//    虽然能编译，但可读性极差。
//
// ⚠️ 9. 提示语 "expreddion" 拼写错误，应为 "expression"。
//
// ⚠️ 10. 用 getchar 读取时，换行符处理虽然用 continue 跳过了，
//    但题目提示建议用 scanf(" %c", &ch)，
//    它能自动跳过空白，代码更简洁。
//
// ✅ 你的栈基本操作（make_empty/is_empty/is_full/push/pop）
//    框架是对的，只是类型和职责要调整。
//
// ============================================================
// * 正确版本（本文件唯一可运行的 main）：
// * 栈存 int，pop 只负责弹一个数，计算在 main 里做。
// * 遇 '=' 弹出栈顶、清空栈、继续下一轮。
// * 遇非法字符退出。
// ============================================================

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100

int stack[STACK_SIZE];   // 栈存 int，中间结果可能大于 9
int top = 0;

void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}

void stack_overflow(void)
{
    printf("Expression is too complex\n");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Not enough operands in expression\n");
    exit(EXIT_FAILURE);
}

void push(int value)
{
    if (is_full())
        stack_overflow();
    stack[top++] = value;
}

int pop(void)
{
    if (is_empty())
        stack_underflow();
    return stack[--top];
}

int main(void)
{
    char ch;

    for (;;) {
        printf("Enter an RPN expression: ");

        // 每轮开始清空栈，确保独立。
        make_empty();

        // 用 scanf(" %c") 读取，自动跳过空白字符。
        while (scanf(" %c", &ch) == 1 && ch != '=') {
            if (ch >= '0' && ch <= '9') {
                push(ch - '0');
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                // 先弹出右操作数，再弹出左操作数。
                int right = pop();
                int left = pop();
                int result;

                switch (ch) {
                    case '+': result = left + right; break;
                    case '-': result = left - right; break;
                    case '*': result = left * right; break;
                    case '/': result = left / right; break;
                    default:  result = 0; break;
                }

                push(result);
            }
            else {
                // 既不是操作数也不是运算符，退出程序。
                return 0;
            }
        }

        // 遇 '=' 或 EOF，弹出栈顶作为结果。
        if (ch == '=') {
            int value = pop();
            printf("Value of expression: %d\n", value);
        }
        else {
            // 输入结束或异常，退出。
            return 0;
        }
    }

    return 0;
}

// ============================================================
// * 验证：
// ============================================================
// 输入 1 2 3 * + =
//   1 压栈 → [1]
//   2 压栈 → [1,2]
//   3 压栈 → [1,2,3]
//   *  弹出 3 和 2，2*3=6 压栈 → [1,6]
//   +  弹出 6 和 1，1+6=7 压栈 → [7]
//   =  弹出 7，输出 7  ✅
//
// 输入 5 8 * 4 9 - / =
//   5 8 * → 40 压栈
//   4 9 - → 4-9 = -5 压栈
//   /   → 40 / -5 = -8 压栈
//   =   → 输出 -8  ✅
//
// 输入 1 2 + + =
//   1 2 + → 3 压栈
//   遇 + 弹出 3，再弹时栈空 → stack_underflow
//   输出 "Not enough operands in expression" 并终止  ✅
//
// 输入 q
//   q 既不是数字也不是运算符 → 退出  ✅
//
// ============================================================
// * 关键修正总结：
// ============================================================
// 1. 栈类型 char → int，解决中间结果大于 9 的错误。
// 2. pop 只负责弹一个数，不再调用 sum 计算。
// 3. 去掉 static sum，结果直接压回栈。
// 4. 遇 '=' 时从栈顶弹出最终结果，而不是用 sum 变量。
// 5. 每轮表达式开始前 make_empty() 清空栈。
// 6. stack_underflow / stack_overflow 的提示语改为本题要求。
// 7. 用 scanf(" %c", &ch) 自动跳过空白，代码更简洁。
// 8. 提示语拼写改为 "expression"。
// ============================================================