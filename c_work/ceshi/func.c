#include <stdio.h>

// 定义：第二维写成4，和声明不一致
void print_arr(int arr[][4]) {
    printf("【函数内部视角】按4列计算步长：\n");
    printf("arr[0][0] = %d\n", arr[0][0]);
    // 按4列算：第1行 = 首地址 + 4*4 = 16字节偏移
    printf("arr[1][0] = %d (实际读到的第2行开头)\n", arr[1][0]);
}
