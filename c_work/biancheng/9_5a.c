// ============================================================
// 第9章 第5题：用函数生成并打印 n×n 幻方
// 题目：
//   void create_magic_square(int n, int magic_square[n][n]);
//   void print_magic_square(int n, int magic_square[n][n]);
//   main 声明 n×n 数组，依次调用两个函数。
// ============================================================

// * 你的代码（逻辑正确，保留原样，在原处标注）：
void create_magic_square(int n, int magic_square[][n]);
void print_magic_square(int n, int magic_square[][n]);

#include <stdio.h>

int main(void)
{
    printf("This program creates a magic square of a specified size.\n");
    printf("The size must be an odd number between 1 and 99.\n");
    printf("Enter size of magic square: ");

    int n;
    scanf("%d", &n);

    // ❌ 错误：只检查了偶数，没检查范围。
    //    n = 0、n = -3 都是“通过”奇数检查的值，但
    //    int square[-3][-3] 是未定义行为。
    //    n = 101 是奇数，但题目说 1~99，也应拒绝。
    //    完整检查应为：
    //      if (n < 1 || n > 99 || n % 2 == 0) { ... return 1; }
    //
    // ⚠️ 提示语 "We will jishu: " 没有讲清楚，建议改成：
    //      printf("Size must be an odd number between 1 and 99.\n");
    if (n % 2 == 0) {
        printf("We will jishu: ");
        return 1;
    }
    // if (n < 1 || n > 99 || n % 2 == 0) {
    //     printf("Size must be an odd number between 1 and 99.\n");
    //     return 1;
    // }

    int square[n][n];
    create_magic_square(n, square);
    print_magic_square(n, square);
    return 0;
}

void create_magic_square(int n, int magic_square[n][n])
{
    // * 初始化数组为 0。
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            magic_square[i][j] = 0;

    int a = 0, b = (n - 1) / 2;
    int j, k;
    magic_square[a][b] = 1;   // ✅ 1 放在第 0 行中间，正确。

    for (int i = 2; i <= n * n; i++) {
        j = a, k = b;   // ✅ 保存上一个位置，碰撞时用得到。
                        // * 你的注释“a 和 b 是上次的值，所以必须得靠它们传”
                        //   ✅ 理解完全正确。

        a -= 1, b += 1; // ✅ 右上移动，用逗号表达式没问题。

        if (a < 0) a = n - 1;   // ✅ 上行越界，绕到最后一行。
        if (b >= n) b = 0;      // ✅ 右列越界，绕到第一列。

        if (magic_square[a][b] == 0)
            magic_square[a][b] = i;
        else {
            // ✅ 碰撞时回滚到正下方。
            // * a = j + 1 在本题算法里不会越界：
            //   对奇数 n 的 Siamese 方法，回滚只会在“上一位置不在最后一行”时发生，
            //   所以 j + 1 <= n - 1，不会出现 a = n。
            //   这是这个算法的一个性质，不是显式检查。
            //   如果想要防御性保险，可以写成 a = (j + 1) % n，
            //   但当前写法对这个算法是安全的，不算错误。
            a = j + 1, b = k;
            magic_square[a][b] = i;
        }
    }
}

void print_magic_square(int n, int magic_square[][n])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // ⚠️ 列宽 %2d 对 n > 9 不够：n = 99 时最大数 9801 占 4 位，
            //    %2d 会破坏对齐。
            //    题目示例看起来是每列 5 个字符宽，建议改成 %5d。
            printf("%2d ", magic_square[i][j]);
        }
        printf("\n");
    }
}

// ============================================================
// * 逐项批改：
// ============================================================
//
// ✅ 函数划分、原型、参数传递都正确：
//   - create_magic_square 和 print_magic_square 都用 VLA 参数，
//     与你只使用 GCC 的环境一致。
//   - 原型用 int magic_square[][n] 和定义用 int magic_square[n][n] 等价，
//     第一维可以省略，都合法。
//   - 函数内修改 magic_square[i][j] 会反映到 main 的 square 数组，
//     因为数组传参本质是指针，正确。
//
// ✅ 幻方生成核心逻辑正确：
//   - 1 放在第 0 行中间。
//   - 每次先算右上，再处理行、列绕回。
//   - 碰撞时回滚到上一个位置的正下方。
//   - 保存 j、k 作为上一个位置，正确。
//   - 你的注释“必须靠它们传”理解正确。
//
// ✅ 关于 a = j + 1 不会越界：
//   对奇数 n 的 Siamese 方法，回滚只会在“上一个位置不在最后一行”时发生，
//   所以 j + 1 <= n - 1，不会出现 a = n。
//   这是算法性质，不是显式检查。
//   如果想加保险，写成 a = (j + 1) % n 也行，但当前写法是安全的。
//
// ❌ 错误：n 的范围检查不完整。
//   只检查了 n % 2 == 0，没有检查 n < 1 || n > 99。
//   n = 0、负数、101 这类输入会导致 VLA 大小为非法值或超出题意。
//   应改成：
//     if (n < 1 || n > 99 || n % 2 == 0) {
//         printf("Size must be an odd number between 1 and 99.\n");
//         return 1;
//     }
//
// ⚠️ 警告 1：错误提示 "We will jishu: " 没有讲清楚问题，
//    建议改成 "Size must be an odd number between 1 and 99.\n"。
//
// ⚠️ 警告 2：printf 列宽 %2d 对较大的 n 不够。
//    n = 99 时最大数 9801 占 4 位，%2d 会破坏对齐。
//    题目示例看起来每列占 5 位，建议改成 %5d。
//
// ⚠️ 小提醒：函数原型写在 #include <stdio.h> 之前，
//    因为原型不需要 stdio，所以能编译；
//    但通常 include 放在最前面，读起来更自然。
//
// ============================================================
// * 最小修正（保留你的结构，只改两处）：
// ============================================================
/*
int main(void)
{
    ...
    scanf("%d", &n);

    if (n < 1 || n > 99 || n % 2 == 0) {
        printf("Size must be an odd number between 1 and 99.\n");
        return 1;
    }

    int square[n][n];
    ...
}

void print_magic_square(int n, int magic_square[][n])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%5d", magic_square[i][j]);   // 改成 %5d
        printf("\n");
    }
}
*/

// ============================================================
// 批改总结：
// ============================================================
// ✅ 核心逻辑完全正确，能生成正确的 n×n 幻方。
// ✅ 函数划分、VLA 参数、数组传参、右上绕回、碰撞回滚都正确。
// ✅ 你的注释“a 和 b 是上次的值，必须靠它们传”理解正确。
// ✅ a = j + 1 在奇数 n 的 Siamese 方法中不会越界，不是错误。
//
// ❌ 错误：n 的合法性检查不完整。
//    只检查了偶数，没检查 n < 1 || n > 99。
//    修正：if (n < 1 || n > 99 || n % 2 == 0) { ... return 1; }
//
// ⚠️ 警告：错误提示 "We will jishu: " 不清楚，建议改成
//    "Size must be an odd number between 1 and 99.\n"。
//
// ⚠️ 警告：printf 列宽 %2d 对 n > 9 不够，建议改成 %5d。
//
// * C23 变化：VLA 在 C23 中变为可选特性。
//   你只用 GCC，GCC 支持 VLA，所以能编译，不判错。
//   如果将来换到不支持 VLA 的编译器，需要按题目说明改成 99×99 固定数组。
// ============================================================