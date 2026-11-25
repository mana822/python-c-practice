// ============================================================
// 第10章 第3题：用 5×2 的 hand 数组存牌，去掉三个计数数组
// 题目：
//   把 num_in_rank、num_in_suit、card_exists 去掉，
//   改用 5×2 数组 hand 存牌，每行一张牌，
//   hand[i][0] 存点数，hand[i][1] 存花色。
//   分析牌型时不能再依赖任何按点数/花色计数的数组。
// ============================================================

// ! 你的原始代码（整段注释，你的笔记用 / 保留，批改见下方）：
/*
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5
#define HANG 5
#define LIE 2

void read_cards(void);
void analyze_hand(void);
void print_result(void);

bool straight, flush, four, three;   / 这是判断类型用的
int pairs = 0;  / 能成为0，1，或2
int hand[HANG][LIE] = {};

int main(void)
{
    for(;;) {
        read_cards();
        analyze_hand();
        print_result();
    }
}
void read_cards(void)
{
    int ch;
    int rank_ch, suit_ch;
    int num = 0;
    while (num < NUM_CARDS) {
        bool bad_card = false;
        printf("Enter a card: ");
        rank_ch = getchar();
        switch (rank_ch) {
            case '0':       exit(EXIT_SUCCESS); / <-- 0就退出
            case '2':       rank_ch = 2; break;
            case '3':       rank_ch = 3; break;
            case '4':       rank_ch = 4; break;
            case '5':       rank_ch = 5; break;
            case '6':       rank_ch = 6; break;
            case '7':       rank_ch = 7; break;
            case '8':       rank_ch = 8; break;
            case '9':       rank_ch = 9; break;
            case 't': case 'T':       rank_ch = 10; break;
            case 'j': case 'J':       rank_ch = 11; break;
            case 'q': case 'Q':       rank_ch = 12; break;
            case 'k': case 'K':       rank_ch = 13; break;
            case 'a': case 'A':       rank_ch = 14; break;
            default:         bad_card = true;    / <-- 只要出错，bad_card为true
        }
        suit_ch = getchar();
        switch (suit_ch) {
        case 'c': case 'C': suit_ch = 0; break;
        case 'd': case 'D': suit_ch = 1; break;
        case 'h': case 'H': suit_ch = 2; break;
        case 's': case 'S': suit_ch = 3; break;
        default:            bad_card = true;   / <-- 一样，只要一个不对就掉
        }

        while ((ch = getchar()) != '\n')
            if (ch != ' ') bad_card = true;

        for (int i = 0; i < num; i++) {
            if (hand[i][0] == rank_ch && hand[i][1] == suit_ch)
                bad_card = true;
            }

        if (bad_card) printf("No! bad card!\n");
        else {
            hand[num][0] = rank_ch; hand[num++][1] = suit_ch;
        }
    }
}
void analyze_hand(void)
{
    straight = true, flush = true, four = false, three = false, pairs = 0;
    for (int i = 1; i < NUM_CARDS; i++)
        if (hand[0][1] != hand[i][1]) flush = false;

    for (int i = 0; i < NUM_CARDS - 1; i++) {
        for (int j = 0; j < NUM_CARDS - 1 - i; j++)
            if (hand[j][0] > hand[j+1][0]) {
                int t = hand[j+1][0];
                hand[j+1][0] = hand[j][0];
                hand[j][0] = t;
            }
    }
    for (int i = 0; i < NUM_CARDS; i++)
        printf("%d\n", hand[i][0]);

    for (int i = 1; i < NUM_CARDS; i++) {
        if (hand[i-1][0]+1 != hand[i][0]) {straight = false;}
    }
    if (straight) return;
    int n = 0, m = 0;
    bool k = true, j = false;
    for (int i = 1; i < NUM_CARDS; i++) {
        if (k && hand[i-1][0] == hand[i][0]) n++;
        else if (n != 0) {k = false, j = true;}

        if (j && hand[i-1][0] == hand[i][0]) m++;
    }
    if (n == 1 && m == 1) pairs += 2;
    else if (n == 1 || m == 1) pairs += 1;
    if (n == 3 || m == 3) four = true;
    else if (n == 2 || m == 2) three = true;
}

void print_result(void)
{
    / 开始逐步判断条件
    if (straight && flush) printf("Straight flush");  / <-- 同花顺
    else if (four) printf("Four of a kind");
    else if (three && pairs == 1) printf("Full house");
    else if (flush) printf("Flush");
    else if (straight) printf("Straight");
    else if (three) printf("Three of a kind");
    else if (pairs == 2) printf("Two pairs");
    else if (pairs == 1) printf("Pair");
    else printf("High card");

    printf("\n\n");
}
*/

// ============================================================
// * 批改：
// ============================================================
// ✅ 符合题目要求：
//    完全去掉 num_in_rank、num_in_suit、card_exists，
//    只用 hand[5][2] 存牌。
//    分析牌型时没有引入任何新的计数数组，
//    直接对排好序的 hand 做比较，符合题目“只用 hand”的要求。
//
// ✅ 你的 n/m 状态机正确：
//    排序后 hand[i][0] 是升序点数。
//    n 记录第一组相同点数的“额外个数”（即组大小 - 1），
//    m 记录第二组相同点数的“额外个数”。
//    对 5 张牌，最多只有两组相同点数，两个变量够用。
//
//    逐牌型验证：
//      四条 5,5,5,5,9    → n=3           → four=true
//      三条 5,5,5,9,10   → n=2           → three=true
//      葫芦 5,5,5,9,9    → n=2, m=1      → three=true, pairs=1
//      两对 5,5,9,9,10   → n=1, m=1      → pairs=2
//      一对 5,5,9,10,J   → n=1, m=0      → pairs=1
//      无对 2,3,4,5,6    → n=0, m=0      → 无对子
//    全部与 print_result 的判断条件对得上。
//
// ✅ 冒泡排序把点数升序排好，供 straight 和 n/m 使用，正确。
// ✅ straight 判断相邻点数差 1，正确。
// ✅ straight 为真时提前 return，正确。
// ✅ flush 在排序前判断，比较第一张牌花色和其余牌花色，正确。
// ✅ read_cards 判重、bad_card 逻辑正确。
//
// ⚠️ 代码质量问题（不影响正确性，但建议清理）：
//
// ⚠️ 1. analyze_hand 里有调试 printf：
//       for (int i = 0; i < NUM_CARDS; i++)
//           printf("%d\n", hand[i][0]);
//    会多输出 5 行点数，干扰 print_result 的显示。
//    程序照样能跑、牌型判断照样对，删掉只是让输出干净。
//
// ⚠️ 2. 冒泡排序只交换点数，不交换花色。
//    排序后 hand[i][0] 和 hand[i][1] 的对应关系被破坏。
//    本题因为 flush 在排序前已经判断完，之后不再用 hand[i][1]，
//    所以实际不影响结果。
//    但这是隐患：如果以后有人在这之后用花色，就会出错。
//    建议点数和花色一起交换。
//
// ⚠️ 3. read_cards 的 while ((ch = getchar()) != '\n') 没判 EOF。
//    正常输入下能退出，输入流提前结束时才会死循环。
//    建议改成 while ((ch = getchar()) != '\n' && ch != EOF)。
//
// ⚠️ 4. "No! bad card!" 不区分坏牌和重复牌。
//    只是提示不够细，不影响正确性。
//
// ⚠️ 5. hand 是全局数组，每局开始没清空。
//    read_cards 总是从 hand[0] 开始写满 5 张，覆盖后没问题。
//    习惯上每局开始前清空更稳，避免以后改动引入隐患。
//
// ✅ 关于 hand[num++][1] = suit_ch;
//    先取 num 写 hand[num][1]，再 num++，顺序正确，
//    等价于“先写后自增”，没有问题。
//
// ============================================================
// * 最小修正版（本文件唯一可运行的 main）：
// * 保留你的 hand 数组和 n/m 状态机；
// * 只删调试 printf、排序时点数和花色一起交换、while 补 EOF 判断。
// * 不引入任何计数数组，符合题目要求。
// ============================================================

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_CARDS 5
#define HANG 5
#define LIE 2

bool straight, flush, four, three;
int pairs = 0;
int hand[HANG][LIE] = {};

void read_cards(void);
void analyze_hand(void);
void print_result(void);

int main(void)
{
    for (;;) {
        read_cards();
        analyze_hand();
        print_result();
    }
}

void read_cards(void)
{
    int ch;
    int rank_ch, suit_ch;
    int num = 0;

    while (num < NUM_CARDS) {
        bool bad_card = false;

        printf("Enter a card: ");
        rank_ch = getchar();

        switch (rank_ch) {
            case '0':           exit(EXIT_SUCCESS);
            case '2': rank_ch = 2;  break;
            case '3': rank_ch = 3;  break;
            case '4': rank_ch = 4;  break;
            case '5': rank_ch = 5;  break;
            case '6': rank_ch = 6;  break;
            case '7': rank_ch = 7;  break;
            case '8': rank_ch = 8;  break;
            case '9': rank_ch = 9;  break;
            case 't': case 'T': rank_ch = 10; break;
            case 'j': case 'J': rank_ch = 11; break;
            case 'q': case 'Q': rank_ch = 12; break;
            case 'k': case 'K': rank_ch = 13; break;
            case 'a': case 'A': rank_ch = 14; break;
            default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit_ch = 0; break;
            case 'd': case 'D': suit_ch = 1; break;
            case 'h': case 'H': suit_ch = 2; break;
            case 's': case 'S': suit_ch = 3; break;
            default:            bad_card = true;
        }

        // 修正：补上 EOF 判断。
        while ((ch = getchar()) != '\n' && ch != EOF)
            if (ch != ' ')
                bad_card = true;

        // 判重：遍历已存的牌。
        for (int i = 0; i < num; i++) {
            if (hand[i][0] == rank_ch && hand[i][1] == suit_ch)
                bad_card = true;
        }

        if (bad_card)
            printf("No! bad card!\n");
        else {
            hand[num][0] = rank_ch;
            hand[num][1] = suit_ch;
            num++;
        }
    }
}

void analyze_hand(void)
{
    straight = true;
    flush = true;
    four = false;
    three = false;
    pairs = 0;

    // 同花：排序前判断，比较第一张牌花色和其余牌花色。
    for (int i = 1; i < NUM_CARDS; i++) {
        if (hand[0][1] != hand[i][1])
            flush = false;
    }

    // 冒泡排序：点数升序，点数和花色一起交换。
    for (int i = 0; i < NUM_CARDS - 1; i++) {
        for (int j = 0; j < NUM_CARDS - 1 - i; j++) {
            if (hand[j][0] > hand[j + 1][0]) {
                int t0 = hand[j][0];
                int t1 = hand[j][1];
                hand[j][0] = hand[j + 1][0];
                hand[j][1] = hand[j + 1][1];
                hand[j + 1][0] = t0;
                hand[j + 1][1] = t1;
            }
        }
    }

    // 删除调试 printf，不再输出中间点数。

    // 顺子：相邻点数差 1。
    for (int i = 1; i < NUM_CARDS; i++) {
        if (hand[i - 1][0] + 1 != hand[i][0])
            straight = false;
    }
    if (straight)
        return;

    // 用你的 n/m 状态机，不引入计数数组。
    int n = 0, m = 0;
    bool k = true, j = false;

    for (int i = 1; i < NUM_CARDS; i++) {
        if (k && hand[i - 1][0] == hand[i][0])
            n++;
        else if (n != 0) {
            k = false;
            j = true;
        }
        // 这里因为我们不关心后面不对会怎么样，因为最多就两块组合，不然还是要先i++，把这次排除
        if (j && hand[i - 1][0] == hand[i][0])
            m++;
    }

    if (n == 1 && m == 1)      pairs += 2;
    else if (n == 1 || m == 1) pairs += 1;

    if (n == 3 || m == 3)      four = true;
    else if (n == 2 || m == 2) three = true;
}

void print_result(void)
{
    if (straight && flush)        printf("Straight flush");
    else if (four)                printf("Four of a kind");
    else if (three && pairs == 1) printf("Full house");
    else if (flush)               printf("Flush");
    else if (straight)            printf("Straight");
    else if (three)               printf("Three of a kind");
    else if (pairs == 2)          printf("Two pairs");
    else if (pairs == 1)          printf("Pair");
    else                          printf("High card");

    printf("\n\n");
}

// ============================================================
// 批改总结：
// ============================================================
// ✅ 你的方案完全符合题目要求：
//    去掉三个计数数组，只用 hand[5][2]，
//    分析牌型不依赖任何新的计数数组。
//
// ✅ 你的 n/m 状态机正确：
//    对 5 张牌的所有牌型（四条、三条、葫芦、两对、一对、无对）
//    都能正确分类，与 print_result 的判断条件一一对应。
//
// ✅ 冒泡排序、straight 判断、flush 判断、straight 提前 return、
//    read_cards 判重和 bad_card 逻辑，都正确。
//
// 本次最小修正（不改变你的思路）：
// 1. 删除 analyze_hand 里的调试 printf。
// 2. 冒泡排序时点数和花色一起交换，避免破坏 hand 的完整性。
// 3. read_cards 的 while 补上 EOF 判断。
//
// 没有引入任何计数数组，你的方案本身就是对的。
// 我上一条用 count[15] 是错的，等同于把 num_in_rank 改个名字，
// 违反了题目要求，撤回。
// ============================================================