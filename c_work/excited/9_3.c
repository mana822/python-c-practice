// ============================================================
// 第9章 9.3节 第9题：下列程序的输出是什么？
// #include <stdio.h>
// void swap(int a, int b);
// int main(void)
// {
//     int i = 1, j = 2;
//     swap (i, j);
//     printf("i = %d, j = %d\n", i, j);
//     return 0;
// }
// void swap(int a, int b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }
// 答:i = 1, j = 2
// ============================================================
// ✅ 正确。C 传值调用，swap 里换的是副本 a、b，main 的 i、j 不变。
// * 验证：运行输出 i = 1, j = 2 ✅
// ? 要真交换须传指针 void swap(int *a, int *b)，调用 swap(&i,&j)。

// ============================================================
// 第9章 9.3节 第10题：编写函数返回值（a、n 为形参，a 是 int 数组，n 是长度）
// (a) 数组 a 中最大的元素。
// (b) 数组 a 中所有元素的平均值。
// (c) 数组 a 中正数元素的数量。
// ============================================================

// 10.答:(a)  —— 你的代码（原样，缩进未改）：
int sum(int a[], int n)
{
    int sum = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > sum) sum = a[i];
    }
    return sum;
}
// ✅ 正确。初始化 a[0] 再逐个比较，逻辑对。
// ⚠️ 局部变量 sum 和函数名 sum 同名，合法（局部遮蔽全局），但可读性差，建议改名 max。
// ⚠️ i 从 0 开始会多比一次 a[0] 自己，无害；从 1 开始更地道。
// * 验证：a={3,1,7,2},n=4 → 7 ✅

// 10.答:(b)
float pin(int a[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}
// ✅ 正确。float sum 累加，sum/n 中 n 会转 float，是浮点除法，对。
// * 验证：a={1,2,3},n=3 → 6/3=2.0 ✅

// 10.答:(c)
int zhen(int a[], int n)
{
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) j++;
    }
    return j;
}
// ✅ 正确。只数 >0 的元素，0 不算，符合题意。
// * 验证：a={-1,2,0,5} → 2 ✅
// 批改总结：✅(a)(b)(c)全对 ⚠️(a)变量名 sum 与函数名同名、i 可从 1 开始

// ============================================================
// 第9章 9.3节 第11题：float compute_GPA(char grades[], int n);
// grades 含 A/B/C/D/F（大小写皆可），n 为长度，返回平均值（A=4,B=3,C=2,D=1,F=0）
// ============================================================

// 11.答:
// #include <ctype.h>
// float compute_GPA(char grades[], int n)
// {
//     int sum;                       ← 你的原样：int sum;  【❌ 未初始化】
//     for (int i = 0; i < n; i++) {
//         switch (toupper(grades[i])) {
//             case 'A': sum += 4; break;
//             case 'B': sum += 3; break;
//             case 'C': sum += 2; break;
//             case 'D': sum += 1; break;
//             default: ; break;
//         }
//     }
//     return (float)sum / n;
// }
// ❌ 唯一错误：int sum; 未初始化就 sum += ...，是未定义行为（垃圾值累加）。
//    一处小补充，直接改在原代码上，只改这一行，不重写、不留第二份。
// ✅ 其余全对：toupper 处理大小写、F 走 default（加0）、(float)sum/n 浮点除法。
// ? C23：toupper 参数严格应传 (unsigned char)grades[i] 或 EOF，本题字母是 ASCII，无碍。
// * 验证：grades={'A','B','F'},n=3 → (4+3+0)/3≈2.333 ✅（sum 初始化为 0 后）
// 批改总结：❌ sum 未初始化（已就地改为 =0） ✅ 其余正确

// —— 改好后（唯一定义，只动了出错那一行）——
#include <ctype.h>
float compute_GPA(char grades[], int n)
{
    int sum = 0;                       // ❌→✅ 补上初始化，其余原样
    for (int i = 0; i < n; i++) {
        switch (toupper(grades[i])) {
            case 'A': sum += 4; break;
            case 'B': sum += 3; break;
            case 'C': sum += 2; break;
            case 'D': sum += 1; break;
            default: ; break;
        }
    }
    return (float)sum / n;
}

// ============================================================
// 第9章 9.3节 第12题：double inner_product(double a[], double b[], int n);
// 返回 a[0]*b[0] + ... + a[n-1]*b[n-1]
// ============================================================

// 12.答:
// double inner_product (double a[], double b[], int n)
// {
//     double sum;                    ← 你的原样：double sum;  【❌ 未初始化】
//     for (int i = 0; i < n; i++) {
//         sum += a[i] * b[i];
//     }
//     return sum;
// }
// ❌ 唯一错误：double sum; 未初始化就累加，未定义行为。
//    一处小补充，直接改在原代码上。
// ✅ 其余正确：逐项相乘累加的结构对。
// * 验证：a={1,2,3},b={4,5,6},n=3 → 4+10+18=32 ✅（sum 初始化后）
// 批改总结：❌ sum 未初始化（已就地改为 =0.0） ✅ 结构正确

// —— 改好后（唯一定义，只动了出错那一行）——
double inner_product (double a[], double b[], int n)
{
    double sum = 0.0;                  // ❌→✅ 补上初始化，其余原样
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

// ============================================================
// 第9章 9.3节 第13题：int evaluate_position(char board[8][8]);
// K/Q/R/B/N/P 为白，k/q/r/b/n/p 为黑；白和 Q=9,R=5,B=3,N=3,P=1，黑同理；
// 返回白和 - 黑和（正=白优，负=黑优）
// ============================================================

// 13.答:  —— 你的原版（整体注释，块内用【】不用 //）：
/*
int evaluate_position(char voard[][8])
{
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 8; i++) {
        for (int n = 0; n < 8; n++) {
            if (voard[i][n] >= 'a') sum1++;
            else sum2++;
        }
    }
    return sum1 - sum2;
}
*/
// ❌ 逻辑完全不符合题意，需整体重写：
//    (1) 没有按棋子分值算，只是 sum1++/sum2++ 数个数。题目要求 Q=9、R=5 等分值。
//    (2) 大小写判断反了：小写是黑子，你却加进 sum1（当白）；大写白子加进 sum2。
//    (3) 空格（'.' 或 ' '）也会被 else 算进 sum2，污染结果。
//    (4) K 未给分应视为 0，不能计入。
// ✅ 形参 char voard[][8] 合法：第一维可省，第二维必须给，写法本身没问题。
// ? 按题目，白黑分值都要按 Q9/R5/B3/N3/P1 算；K 是王不计分。
// * 验证：白后(Q=9)+车(R=5)，黑车(5)+兵(1) → 白14 - 黑6 = 8
// 批改总结：❌没算分值 ❌大小写反了 ❌空格被计入 ✅形参声明合法
// ------------------------------------------------------------
int evaluate_position(char board[8][8])
{
    int white = 0, black = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case 'Q': white += 9; break;
                case 'R': white += 5; break;
                case 'B': white += 3; break;
                case 'N': white += 3; break;
                case 'P': white += 1; break;
                case 'q': black += 9; break;
                case 'r': black += 5; break;
                case 'b': black += 3; break;
                case 'n': black += 3; break;
                case 'p': black += 1; break;
                default: break;          // K、空格不计分
            }
        }
    }
    return white - black;
}
// * 验证修正版：白后+车=14，黑车+兵=6 → 8 ✅
