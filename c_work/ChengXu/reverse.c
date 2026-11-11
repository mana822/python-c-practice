#include <stdio.h>

#define N 10
int main(void)
{
    int a[N], i;     //  <-- 数组创建要声明类型

    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &a[i]);

    printf("In reverse order: ");
    for (i = N - 1; i >= 0; i--)    // <-- 从N-1开始，到0结束，刚好是倒着来
        printf(" %d", a[i]);
    printf("\n");
    return 0;
}

// 这个程序说明了宏和数组的联合使用可以有多么有效，如果以后需要改变数组的大小，只需要编译N的定义并且重新编译程序就行了