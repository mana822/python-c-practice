#include <stdio.h>
void print_pun(void)   // 有些函数根本没有形式参数
{
    printf("To C, or not to C: that is the question.\n");
}
int main(void)
{
    print_pun();
    return 0;
}