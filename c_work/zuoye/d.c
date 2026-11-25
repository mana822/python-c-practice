#include <stdio.h>

void hanoi(int n, char a, char b, char c)
{
    if (n == 1)
    {
        printf("%c->%c\n", a, b);
        return;
    }
    hanoi(n - 1, a, c, b);   // n-1：a → c，借 b
    printf("%c->%c\n", a, b); // 大盘：a → b
    hanoi(n - 1, c, b, a);   // n-1：c → b，借 a
}

int main(void)
{
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
