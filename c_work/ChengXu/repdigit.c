#include <stdio.h>
#include <stdbool.h>  /*C99 only*/

int main(void)
{
    bool digit_seen[10] = {false};     // <-- 全部初始化为false(0)
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit])
            break;
        digit_seen[digit] = true;    // <-- 赋值为true(1)  拿到一次一样的下标就弄为真
        n /= 10;
    }
    if (n > 0)   // <-- 如果上面筛选出来了一样的，那么n就不会为0
        printf("Repeated digit\n");
    else
        printf("No repeated digit\n");
    
    return 0;
}