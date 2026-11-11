// ============================================================
// 第8章 第1题：修改 repdigit.c，显示哪些数字有重复
// 题目：
//   Enter a number: 939577
//   Repeated digit(s): 7 9
// ============================================================

// ! 你的原始代码（整体注释，避免与下面可运行版本冲突）：
/*
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int n, digit, i=-1;
    bool digit_seen[10] = {false};
    int num[5] = {0};

    printf("Enter a number: ");
    scanf("%d", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit]) {
            i++;
            num[i] = digit;
        }

        digit_seen[digit] = true;
        n /= 10;
    }
    if (i >= 0) {
        printf("Repeated digit:");
        for (; i >= 0; i--) {
            printf("%d ", num[i]);}
        }
    else
        printf("No repeated digit\n");

    return 0;
}
*/

// * 批改：
//
// ✅ 核心思路正确：
//   用 digit_seen 标记已经出现过的数字，
//   再次遇到时记录到 num 里，最后输出。
//
// ❌ 严重错误 1：num[5] 太小，可能越界。
//   0~9 共 10 个数字，理论上最多 9 个数字可能重复，
//   比如输入 10012233445566778899，0~9 每个都重复，
//   需要记录 10 个重复数字，num[5] 装不下，会越界写。
//   应改为 int num[10]; 或直接用 bool repeated[10]。
//
// ❌ 错误 2：同一个数字重复多次会被记录多次。
//   例如输入 777：
//     第一次 7：digit_seen[7] 为 false，不记录，标记 seen。
//     第二次 7：digit_seen[7] 为 true，记录 7。
//     第三次 7：digit_seen[7] 仍为 true，又记录一次 7。
//   最终 num = {7, 7}，倒序输出 "7 7"，
//   但题目要求每个重复数字只显示一次，应输出 "7"。
//   正确做法：用另一个 bool repeated[10]，
//   第一次发现重复时标记 repeated[digit] = true，
//   最后遍历 0~9 输出所有 repeated 为 true 的数字。
//
// ⚠️ 警告 3：输出顺序与题目示例相反。
//   你的 num 按从低位到高位记录，倒序打印后得到高位到低位的顺序。
//   输入 939577：
//     从右往左读：7,7,5,9,3,9
//     第一次 7 不重复；第二次 7 重复，记录 7；
//     5 不重复；9 不重复；3 不重复；9 重复，记录 9。
//     num = {7, 9}，倒序输出 "9 7"。
//   题目示例是 "7 9"。
//   虽然顺序不影响“哪些数字重复”，但和示例不一致。
//   用 repeated[10] 从 0 到 9 遍历，输出顺序就是 7 9，与示例一致。
//
// ⚠️ 警告 4：输出格式少了 (s)，且没有换行。
//   题目示例是 "Repeated digit(s): "，你写的是 "Repeated digit:"。
//   末尾建议加 \n。
//
// ? C23 变化：
//   C23 起 bool、true、false 是关键字，
//   不需要 #include <stdbool.h>。
//   但包含它也没有错，头文件仍然存在。
//   下面修正版按 C23 写，不再包含 <stdbool.h>。
//
// ------------------------------------------------------------
// * 修正版（本文件唯一可运行的 main）：
// * 用 seen 标记出现过，用 repeated 标记重复过，
// * 最后遍历 0~9 输出所有重复数字。
// ------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
int main(void)
{
    int n, digit;
    bool seen[10] = {false};       // * 记录数字是否出现过
    bool repeated[10] = {false};   // * 记录数字是否重复过

    printf("Enter a number: ");
    scanf("%d", &n);

    while (n > 0) {
        digit = n % 10;

        if (seen[digit]) {
            // * 已经出现过，标记为重复。
            // * 不管重复几次，repeated[digit] 只置 true 一次，
            // * 所以每个重复数字只输出一次。
            repeated[digit] = true;   // <-- 下标既对应数组的位置，下标的的值也是如此
        } else {
            // * 第一次出现，标记 seen。
            seen[digit] = true;
        }

        n /= 10;
    }

    // * 从 0 到 9 遍历，输出所有重复数字。
    // * 这样顺序是从小到大，且每个数字只输出一次。
    bool found = false;
    printf("Repeated digit(s):");
    for (int i = 0; i < 10; i++) {
        if (repeated[i]) {
            printf(" %d", i);
            found = true;
        }
    }

    if (!found)
        printf(" No repeated digit");

    printf("\n");
    return 0;
}

// * 验证：
//   输入 939577：
//     从右往左：7,7,5,9,3,9
//     7 第二次出现 → repeated[7]=true
//     9 第二次出现 → repeated[9]=true
//     遍历 0~9，输出 7 9
//     结果：Repeated digit(s): 7 9  ✅
//
//   输入 777：
//     7 第二次、第三次出现 → repeated[7]=true
//     输出：Repeated digit(s): 7  ✅
//
//   输入 12345：
//     没有重复，输出：Repeated digit(s): No repeated digit  ✅
//
//   输入 10012233445566778899：
//     0~9 全部重复，repeated 全部为 true，
//     num[10] 不再越界，输出 0 1 2 3 4 5 6 7 8 9  ✅

// ============================================================
// 批改总结：
// ✅ 核心思路正确：seen 标记出现，重复时记录。
// ❌ num[5] 太小，最多可能记录 10 个重复数字，会越界。
// ❌ 同一数字重复多次会被记录多次，应只输出一次。
// ⚠️ 输出顺序与示例相反，用 repeated[10] 遍历 0~9 可解决。
// ⚠️ 输出格式少了 (s)，末尾建议加 \n。
// * C23 变化：bool/true/false 是关键字，不需要 <stdbool.h>。
// * 修正版用 seen + repeated 两个 bool 数组，
//   每个重复数字只输出一次，顺序从小到大，不会越界。
// ============================================================