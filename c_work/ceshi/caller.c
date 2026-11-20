#include <stdio.h>

// 声明：二维数组第二维长度为3
void print_arr(int arr[][3]);

int main(void) {
    // 真实数组：2行3列，内存顺序：1,2,3, 4,5,6
    int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("【调用方视角】按3列计算：\n");
    printf("arr[0][0] = %d\n", arr[0][0]);
    printf("arr[1][0] = %d (预期第2行开头，值为4)\n\n", arr[1][0]);

    print_arr(arr);
    return 0;
}
