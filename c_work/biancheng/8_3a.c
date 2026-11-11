// ============================================================
// 第8章 第3题：输入多个数，判断是否有重复数字，输入 <= 0 时终止
// 题目：
//   修改 8.1 节的 repdigit.c，使得用户可以输入多个数进行重复数字判断。
//   当用户输入的数小于或等于 0 时，程序终止。
// ============================================================

// ! 你的原始代码（整体注释，避免与下面可运行版本冲突）：
/*
#include <stdio.h>
#include <stdbool.h>  C99 only

int main(void)
{
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);
    while (n != 0) {
        bool digit_seen[10] = {false};
        while (n > 0) {
            digit = n % 10;
            if (digit_seen[digit])
                break;
            digit_seen[digit] = true;
            n /= 10;
        }
        if (n > 0)
            printf("Repeated digit\n");
        else
            printf("No repeated digit\n");
        scanf("%ld", &n);
    }
    return 0;
}
*/

// * 批改：
//
// ✅ 核心逻辑正确：
//   - digit_seen 放在外层循环内部、内层循环之前，
//     每次处理新数时重新初始化为 false，正确。
//   - 内层 while 逐位检查，遇到重复就 break，正确。
//   - 用 n > 0 判断是否有重复：有重复时 break 留下非 0 的 n，
//     无重复时 n 减到 0，这个技巧正确。
//   - 每次处理完再 scanf 读下一个数，结构正确。
//
// ❌ 关键错误：外层循环条件应为 n > 0，不是 n != 0。
//   题目要求“输入的数小于或等于 0 时终止”，
//   但 n != 0 只排除了 0，负数仍会进入循环。
//   例如用户输入 -5：
//     n != 0 成立 → 进入循环
//     内层 while (n > 0) 不执行
//     if (n > 0) 为假 → 打印 No repeated digit
//     再 scanf 读下一个
//   负数没有终止程序，反而被当成“无重复”处理，不符合题意。
//   应改为：
//     while (n > 0) {
//
// ⚠️ 警告 1：注释“所以放外面”表述有歧义。
//   digit_seen 实际是在外层循环内部、内层循环之前声明的，
//   每次外层循环重新初始化。
//   建议改成：
//     “放在外层循环内部、内层循环之前，
//      每次处理新数时重新初始化。”
//
// ⚠️ 警告 2：C23 下 bool/true/false 是关键字，
//   不需要 #include <stdbool.h>。
//   包含它也不报错，但可以删掉。
//
// ⚠️ 警告 3：输出末尾建议加 \n。
//
// ? 补充：
//   如果第一次输入就是 0 或负数，while (n > 0) 条件不成立，
//   循环不进入，程序直接结束，符合“<= 0 终止”的要求。
//
// ------------------------------------------------------------
// * 修正版（本文件唯一可运行的 main）：
// ------------------------------------------------------------

#include <stdio.h>

#include <stdbool.h>
int main(void)
{
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    // * 修正：n > 0，输入 <= 0 时终止。
    while (n > 0) {
        // * 每次处理新数时重新初始化 digit_seen。
        bool digit_seen[10] = {false};

        // * 逐位检查，遇到重复就 break。
        while (n > 0) {
            digit = n % 10;
            if (digit_seen[digit])
                break;
            digit_seen[digit] = true;
            n /= 10;
        }

        // * 有重复时 break 留下非 0 的 n，无重复时 n 减到 0。
        if (n > 0)
            printf("Repeated digit\n");
        else
            printf("No repeated digit\n");

        // * 读下一个数，供下一轮 while 判断。
        printf("Enter a number: ");
        scanf("%ld", &n);
    }

    return 0;
}

// * 验证：
//   输入 939577 → Repeated digit
//   输入 12345  → No repeated digit
//   输入 777    → Repeated digit
//   输入 0      → 程序结束
//   输入 -5     → 程序结束  ✅（修正后负数也能终止）

// ============================================================
// 批改总结：
// ✅ digit_seen 每次外层循环重新初始化，正确。
// ✅ 内层逐位检查、break、用 n > 0 判断重复，逻辑正确。
// ❌ 外层条件应为 n > 0，不是 n != 0；
//    n != 0 会让负数进入循环，不符合“<= 0 终止”。
// ⚠️ 注释“放外面”有歧义，应说明是“外层循环内部、内层循环之前”。
// ⚠️ C23 下 <stdbool.h> 可删，bool/true/false 已是关键字。
// ⚠️ 输出建议加 \n。
// * 修正后输入 0 或负数都能正确终止。
// ============================================================