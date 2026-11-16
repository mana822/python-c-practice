#include <stdio.h>

// 注意这里我们把average的函数定义放在了main函数前面。9.2节我们可以看到定义在后面可能会有问题
double average(double a, double b) {    // 形参位置要声明，相当于占用开辟了内存
// double代表了返回的值，隐形转换也会向着它发生
    return (a + b) / 2;
}
int main(void)
{
    double x, y, z;
    printf("Enter three numbers: ");
    scanf("%lf%lf%lf", &x, &y, &z);
    printf("Average of %g and %g: %g\n", x, y, average(x, y));
    printf("Average of %g and %g: %g\n",y, z, average(y, z));
    printf("Average of %g and %g: %g\n", x, z, average(x, z));

    return 0;

}