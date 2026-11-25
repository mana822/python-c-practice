#include <stdio.h>

int main(void)
{
    int n, k, sum = 0, m;
    scanf("%d%d", &n, &k);
    m = k;
    if (n % 2 == 0) n -= 1;
    for (int j = n; j >= 1; j -= 2) {
        if (j == 1) j = 2;
        int a = 0;
        for (int i = 3; i < j; i++) {   // <-- 2直接放行
        if (j % i == 0) {a = 1; break;}
        }
        if (a) continue;
        sum += j;
        if (k == m) {printf("%d", j);}
        else printf("+%d", j);
        k--;
        if (k == 0) break;
    }
    printf("=%d", sum);
    return 0;
}