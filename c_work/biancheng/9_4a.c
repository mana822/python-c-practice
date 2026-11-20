// ============================================================
// 第9章 第4题：用函数判断两个单词是否为变位词
// 题目：
//   void read_word(int counts[26]);
//   bool equal_array(int counts1[26], int counts2[26]);
//   main 调用 read_word 两次读两个单词，
//   再调用 equal_array 判断两个计数数组是否相同。
// ============================================================

// * 你的代码（逻辑完全正确，保留原样，在原处标注）：
#include <stdio.h>
#include <stdbool.h>   // * C23 下 bool/true/false 已是关键字，
                       //   这个头文件可以删掉；包含它也不报错。
#include <ctype.h>

void read_word(int counts[26]);
bool equal_array(int counts1[26], int counts2[26]);

int main(void)
{
    int counts1[26] = {};   // * C23 空初始化器合法，全部为 0。
    int counts2[26] = {};   // * 只用 GCC 的话没问题；标准 C99 需写 {0}。

    printf("Enter first word: ");
    read_word(counts1);     // ✅ 传数组名，等价于传首元素地址，函数内修改会反映到 counts1。

    printf("Enter second word: ");
    read_word(counts2);

    if (equal_array(counts1, counts2))
        printf("The words are anagrams.");        // ⚠️ 建议末尾加 \n
    else
        printf("The words are not anagrams.");    // ⚠️ 建议末尾加 \n

    return 0;   // ✅ 显式写出，规范。
}

void read_word(int counts[26])
{
    int m;

    // ✅ m 用 int 接收 getchar，能正确判断 EOF。
    // ✅ while 条件同时排除 EOF 和换行，正确。
    while ((m = getchar()) != EOF && m != '\n') {

        // ✅ 只处理字母，非字母直接跳过，符合题目要求。
        // * 这里 isalpha(m) 和 tolower(m) 直接传 m 是安全的：
        //   m 来自 getchar，值域是 0~255 或 EOF，
        //   而 while 条件已排除 EOF，所以 m 一定在 0~255 内，
        //   满足 isalpha/tolower 对参数的要求（unsigned char 值或 EOF）。
        //   不需要额外强转 (unsigned char)，这一点你做对了。
        if (isalpha(m)) {
            m = tolower(m);         // ✅ 统一转小写，大小写不敏感。
            counts[m - 'a']++;      // ✅ 小写字母映射到 0~25，计数 +1。
        }
        else
            continue;   // ⚠️ 这里的 continue 是多余的：
                        //    循环体本来就只有 if，没有后续语句，
                        //    不写 continue 也会自然进入下一轮。
                        //    删掉不影响逻辑，代码更干净。
    }
}

bool equal_array(int counts1[26], int counts2[26])
{
    // ✅ 逐元素比较，只要有一个不同就返回 false，全部相同返回 true。
    for (int i = 0; i < 26; i++) {
        if (counts1[i] != counts2[i])
            return false;
    }
    return true;
}

// * 验证：
//   输入 smartest 和 mattress
//   counts1 与 counts2 完全一致 → equal_array 返回 true → anagrams  ✅
//
//   输入 dumbest 和 stumble
//   counts1 中 d=1、l=0，counts2 中 d=0、l=1，
//   第 3 个元素（d）就不同 → 返回 false → not anagrams  ✅
//
//   输入 Smartest 和 MATTRESS（大小写混合）
//   tolower 统一转小写，计数一致 → anagrams  ✅

// ============================================================
// 批改总结：
// ============================================================
// ✅ 完全正确，函数划分、参数传递、计数逻辑、比较逻辑都没问题。
//
// 逐项核对：
// ✅ read_word 参数 int counts[26] 等价于 int *counts，函数内修改会反映到原数组。
// ✅ m 用 int 接收 getchar，能正确判断 EOF。
// ✅ while 条件同时排除 EOF 和换行，正确。
// ✅ isalpha/tolower 直接传 m 是安全的，不需要强转 unsigned char。
// ✅ counts[m - 'a']++ 映射正确，大小写不敏感。
// ✅ equal_array 逐元素比较，有一个不同就 false，全部相同才 true。
// ✅ 两个计数数组都初始化为 0。
//
// ⚠️ 小建议（不是错误）：
//   1. 两个 printf 末尾建议加 \n，输出更整洁。
//   2. read_word 里的 else continue; 是多余的，
//      循环体只有 if，不写 continue 也会进入下一轮，删掉更干净。
//   3. <stdbool.h> 在 C23 下可以删掉，bool/true/false 已是关键字；
//      包含它也不报错，保留也没问题。
//
// ? 你的注释“判等的条件与判不等截然不同”：
//   我理解你想说的是 equal_array 的写法——
//   不是“统计有多少个相同”，而是“找到一个不同就立刻返回 false，
//   全部走完才返回 true”。
//   这个理解是对的：判等用“找反例”，判不等用“找正例”，
//   逻辑方向确实相反。
//
// ? C23 变化：
//   - bool/true/false 是关键字，<stdbool.h> 可删。
//   - 空初始化器 {} 合法。
//   - isalpha/tolower 规则不变，参数仍需注意 unsigned char 值或 EOF，
//     本题 m 来自 getchar，已在安全范围内。
// ============================================================