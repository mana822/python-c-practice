#include <stdio.h>
void num(int n)
{
    if (n == 0) return;
    num(n / 2);
    putchar('0' + n % 2);
}
int main(void)
{
    int n;
    while ((scanf("%d", &n)) != EOF) {
        num(n);
        printf("\n");
    }
    return 0;
}