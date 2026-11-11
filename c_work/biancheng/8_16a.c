// 16. 编程测试两个单词是否为变位词（相同字母的重新排列）：

// Enter first word: smartest
// Enter second word: mattress
// The words are anagrams.

// Enter first word: dumbest
// Enter second word: stumble
// The words are not anagrams.

// 用一个循环逐个字符地读取第一个单词，用一个 26 元的整数数组记录每个字母的出现次数。
// （例如，读取单词 smartest 之后，数组包含的值为 10001000000010000122000000，表明 smartest 包含一个 a、一个 e、一个 m、一个 r、两个 s 和两个 t。）
// 用另一个循环读取第二个单词，这次每读取一个字母就把相应数组元素的值减 1。两个循环都应该忽略不是字母的那些字符，并且不区分大小写。
// 第二个单词读取完毕后，再用一个循环来检查数组元素是否全为 0。如果是全 0，那么这两个单词就是变位词。
// 提示：可以使用 <ctype.h> 中的函数，如 isalpha 和 tolower。

#include <stdio.h>
// 刚看到题目我第一个想到用循环暴力破解，结果由题目可知可以计数，一想到计数，我就想到下标值对应位置
// 发现isalpha和tolower这两个没见过的函数，到时候ai记得补充，我就不用了
int main(void)
{
    int j, m;
    int list[26] = {};  // <-- 26个字母，26个下标，准备了26个格子
    printf("Enter first word:  ");
    while ((j = getchar()) != EOF && j != '\n' ) { // <-- 经典连招，朴实无华,getchar()无溢出风险
        if (j >= 'a' && j <= 'z') {
        j -= 'a';    // <-- 直接减'a'对应下标0，由于是小写就不判断了，当然，会有bug，但是会多出很多工程判断
        list[j]++; }  // <-- 这就是下标对应位置，下标也是一个标识符啊
        else if (j >= 'A' && j <= 'Z') {
            j -= 'A';
            list[j]++;
        }
        else continue;
    }
    // 第一个集结完毕，准备搞第二个
    printf("Enter second word: ");
    while ((m = getchar()) != EOF && m != '\n') {
        if (m >= 'a' && m <= 'z') {     // 响应题目，无视非字母字符
        m -= 'a';    
        list[m]--; }  
        else if (m >= 'A' && m <= 'Z') {    // 响应题目，会略大小写，它们都互相对应，-'a'或-'A'都是初始化为0
            m -= 'A';
            list[m]--;
        }
        else continue;
    }
    // 现在我们要查看所有元素，如果都为0那就是true
    int a = 0;    // 弄一个计数器记录0的次数
    for (int i = 0; i < 26; i++) {
        if (list[i] == 0) a++;
    }
    if (a == 26) printf("The words are anagrams.");
    else printf("The words are not anagrams.");
    // 当然也可以判断只要有一个不是0就可以了
    return 0;

}


// ============================================================
// 第8章 第16题：判断两个单词是否为变位词（anagram）
// 题目：
//   Enter first word: smartest
//   Enter second word: mattress
//   The words are anagrams.
//
//   用 26 元整数数组记录字母出现次数，
//   第一个单词每个字母对应计数 +1，第二个单词 -1，
//   最后检查是否全为 0。忽略非字母字符，不区分大小写。
// ============================================================

// * 你的代码（逻辑完全正确，保留原样，在原处标注）：
#include <stdio.h>

int main(void)
{
    int j, m;
    int list[26] = {};   // * C23 空初始化器合法，26 个格子全部初始化为 0。
                         // * 你的注释“26 个字母，26 个下标，准备了 26 个格子” ✅ 正确。

    printf("Enter first word:  ");

    // ✅ 第一个循环：逐字符读，小写和大写分别映射到 0~25，计数 +1。
    // * 你的注释“经典连招，朴实无华，getchar() 无溢出风险”
    //   ✅ 正确。getchar 返回 int，用 int 接收，能正确判断 EOF。
    while ((j = getchar()) != EOF && j != '\n') {
        if (j >= 'a' && j <= 'z') {
            j -= 'a';    // * 小写 a~z 映射到 0~25。
            list[j]++;   // * 你的注释“下标对应位置，下标也是一个标识符”
                         //   ✅ 正确。字符减去 'a' 得到 0~25 的整数，正好做数组下标。
        }
        else if (j >= 'A' && j <= 'Z') {
            j -= 'A';    // * 大写 A~Z 也映射到 0~25。
            list[j]++;   // * 大小写共用同一个计数格子，实现不区分大小写。
        }
        else continue;   // * 非字母字符直接跳过，符合题目“忽略非字母字符”。
    }

    printf("Enter second word: ");

    // ✅ 第二个循环：同样的映射，但计数 -1。
    // * 第一个单词贡献 +1，第二个单词贡献 -1，
    //   如果两个单词字母组成相同，最终每个格子都会抵消回 0。
    while ((m = getchar()) != EOF && m != '\n') {
        if (m >= 'a' && m <= 'z') {
            m -= 'a';
            list[m]--;
        }
        else if (m >= 'A' && m <= 'Z') {
            m -= 'A';
            list[m]--;
        }
        else continue;
    }

    // ✅ 检查所有格子是否全为 0。
    // * 你的注释“弄一个计数器记录 0 的次数” ✅ 思路正确。
    int a = 0;
    for (int i = 0; i < 26; i++) {
        if (list[i] == 0) a++;
    }

    // ✅ 输出结果。
    // * 你的注释“当然也可以判断只要有一个不是 0 就可以了”
    //   ✅ 正确。两种写法等价：
    //     - 统计 0 的个数，等于 26 则 anagrams；
    //     - 或找一个非 0，找到就 not anagrams，找不到则 anagrams。
    if (a == 26)
        printf("The words are anagrams.");   // ⚠️ 微调：末尾建议加 \n。
    else
        printf("The words are not anagrams.");

    return 0;
}

// * 验证：
//   输入 smartest 和 mattress
//   第一个单词：s=2, m=1, a=1, r=1, t=2, e=1
//   第二个单词：m=1, a=1, t=2, r=1, e=1, s=2
//   抵消后全为 0 → anagrams  ✅
//
//   输入 dumbest 和 stumble
//   第一个单词：d=1, u=1, m=1, b=1, e=1, s=1, t=1
//   第二个单词：s=1, t=1, u=1, m=1, b=1, l=1, e=1
//   抵消后 d=1, l=1 不为 0 → not anagrams  ✅
//
//   输入 Smartest 和 MATTRESS（大小写混合）
//   大小写映射到同一组格子，结果仍然是 anagrams  ✅

// ============================================================
// 批改总结：
// ✅ 完全正确，没有逻辑错误。
//
// 逐项核对：
// ✅ list[26] 空初始化器在 C23 合法，全部为 0。
// ✅ j、m 用 int 接收 getchar，能正确判断 EOF。
// ✅ 小写和大写分别映射到 0~25，大小写共用计数格子，实现不区分大小写。
// ✅ 非字母字符 continue 跳过，符合题目要求。
// ✅ 第一个单词 +1，第二个单词 -1，抵消后检查是否全 0，逻辑正确。
// ✅ 统计 0 的个数再和 26 比较，正确；也可以改成找一个非 0 就 break。
//
// ⚠️ 微调（不是错误）：
//   1. 两个 printf 末尾建议加 \n，输出更整洁。
//   2. 变量名 j、m 用来存字符，可读性一般。
//      建议改成 int ch;，两个循环复用同一个变量，
//      因为第一个循环结束后 j 的值不再需要。
//      但你现在分两个变量也能跑对，不是错误。
//   3. 你的注释“会有 bug，但是会多出很多工程判断”
//      如果指的是“不区分大小写就要多写一堆判断”，
//      其实你已经用 else if 分别处理了大写和小写，
//      没有额外 bug。这句注释可以删掉，避免以后自己看混。
//
// ? 关于你提到的 isalpha 和 tolower：
//   - isalpha(c)：判断 c 是否为字母，返回非 0 表示是字母，0 表示不是。
//     参数要求是 unsigned char 的值或 EOF，所以写 isalpha((unsigned char)ch)。
//   - tolower(c)：如果是大写字母，返回对应小写；否则原样返回。
//     参数同样建议转 (unsigned char)。
//   用这两个函数可以简化代码：
//
//     while ((ch = getchar()) != '\n' && ch != EOF) {
//         if (isalpha((unsigned char)ch)) {
//             ch = tolower((unsigned char)ch);
//             list[ch - 'a']++;
//         }
//     }
//
//   第二个循环同理，只是把 ++ 改成 --。
//   效果和你现在的代码完全一样，只是少写了大写分支。
//   你现在的代码不依赖这两个函数，逻辑也完全正确。
//
// ? C23 变化：
//   - int list[26] = {}; 空初始化器在 C23 合法，C99/C11 需写 {0}。
//   - isalpha、tolower 在 C23 下规则不变，参数仍需注意 unsigned char。
// ============================================================