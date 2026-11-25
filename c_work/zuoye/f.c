#include <stdio.h>

int trans(int n)
{
    if (n == 0) return 0;
    long long res = 0;
    long long pow10 = 1;
    int stack[32], top = 0;
    // 收集二进制位
    while (n > 0)
    {
        stack[top++] = n % 2;
        n /= 2;
    }
    // 倒着拼，得到正确顺序
    for (int i = top - 1; i >= 0; i--)
    {
        res = res * 10 + stack[i];
    }
    return (int)res;
}

int main(void)
{
    int x;
    // PTA：读到流结束；本地需要 Ctrl+Z / Ctrl+D
    while (scanf("%d", &x) != EOF)
    {
        int r = trans(x);
        printf("%d\n", r);
    }
    return 0;
}
