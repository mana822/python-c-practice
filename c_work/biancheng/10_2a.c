// ============================================================
// 第10章 第2题：把 num_in_rank 和 num_in_suit 移到 main 中
// 题目：
//   修改 10.5 节的 poker.c，把两个数组移到 main 函数中，
//   main 把它们作为实参传给 read_cards 和 analyze_hand。
// ============================================================

// ! 你的原始代码（整段注释，你的笔记用 / 保留，批改见下方）：
/*
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

bool straight, flush, four, three;
int pairs = 0;
void read_cards(char[], char[]);
void analyze_hand(char[], char[]);
void print_result(void);

int main(void)
{
    while (true) {
        char num_in_rank[NUM_RANKS] = {}, num_in_suit[NUM_SUITS] = {};
        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit);
        print_result();
    }
}
void read_cards(char num_in_rank[], char num_in_suit[])
{
    int rank_ch, suit_ch, rank = 0, suit = 0, ch;
    int num = 0;
    bool panduan[NUM_RANKS][NUM_SUITS] = {false};
    while (num < NUM_CARDS) {
        bool bad_card = false;
        printf("Enter a card: ");
        rank_ch = getchar();     / <-- 拿第一个数
        switch (rank_ch) {
            case '0':       exit(EXIT_SUCCESS); / <-- 0就退出
            case '2':       rank = 0; break;
            case '3':       rank = 1; break;
            case '4':       rank = 2; break;
            case '5':       rank = 3; break;
            case '6':       rank = 4; break;
            case '7':       rank = 5; break;
            case '8':       rank = 6; break;
            case '9':       rank = 7; break;
            case 't': case 'T':       rank = 8; break;
            case 'j': case 'J':       rank = 9; break;
            case 'q': case 'Q':       rank = 10; break;
            case 'k': case 'K':       rank = 11; break;
            case 'a': case 'A':       rank = 12; break;
            default:         bad_card = true;    / <-- 只要出错，bad_card为true
        }
        / 先不急去加数组，我们要判断，对了加。
        suit_ch = getchar();      / <-- 再拿花色
        switch (suit_ch) {
        case 'c': case 'C': suit = 0; break;
        case 'd': case 'D': suit = 1; break;
        case 'h': case 'H': suit = 2; break;
        case 's': case 'S': suit = 3; break;
        default:            bad_card = true;   / <-- 一样，只要一个不对就掉

        }
        while ((ch = getchar()) != '\n' && ch != EOF)
            if (ch != ' ') bad_card = true;
        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (panduan[rank][suit])     / <-- 这是判断重复，第一轮用不上
            printf("Duplicat card; ignored.\n");
        else {         / <-- 只要是有错误，后面的改变不执行，计数器也不增加，相当于continue
            num_in_rank[rank]++;            / <-- 标记位置，用自增来标记
            num_in_suit[suit]++;
            panduan[rank][suit] = true;    / <-- 用下标当位置，来计算是否重复
            num++;              / <-- 计数器加一
            }
    }
}

void analyze_hand(char num_in_rank[], char num_in_suit[])
{
    straight = false, flush = false, four = false, three = false;
    pairs = 0;
    int num = 0, rank = 0;
    for (int i = 0; i < NUM_SUITS; i++)
        if (num_in_suit[i] == NUM_SUITS)
            straight = true;
    for (rank = 0; rank < NUM_RANKS; rank++)
        while (num_in_rank[rank] != 0) break;
    for (; num_in_rank[rank] > 0 && rank < NUM_RANKS; rank++)  / <-- 这个判断还是留一手
        num++;
    if (num == NUM_CARDS) flush = true;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (num_in_rank[i] == 4) four = true;
        if (num_in_rank[i] == 3) three = true;
        if (num_in_rank[i] == 2) pairs++;
    }
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
// ✅ 对的：
// 1. main 里把两个数组声明在 while 循环内部，每局重新初始化，
//    然后传给 read_cards 和 analyze_hand，结构符合题目要求。
// 2. read_cards 的 rank/suit 映射、panduan 判重、bad_card 逻辑都正确。
// 3. print_result 的判定顺序正确。
// 4. 你的注释“用自增来标记”“用下标当位置，来计算是否重复”
//    “只要有一个不对就掉”“相当于 continue”都理解正确。
//
// ❌ 错误（全部在 analyze_hand）：
//
// 错误 1：flush 判断写成了 straight，且条件用错了常量。
//   for (int i = 0; i < NUM_SUITS; i++)
//       if (num_in_suit[i] == NUM_SUITS)
//           straight = true;
//   - 这里应该判断 flush，不是 straight。
//   - 条件应该是 num_in_suit[i] == NUM_CARDS（5 张同花），
//     不是 == NUM_SUITS（4 种花色）。
//   原书 poker.c 是：
//     for (suit = 0; suit < NUM_SUITS; suit++)
//         if (num_in_suit[suit] == NUM_CARDS)
//             flush = true;
//
// 错误 2：straight 判断逻辑完全错误，并且会越界。
//   for (rank = 0; rank < NUM_RANKS; rank++)
//       while (num_in_rank[rank] != 0) break;
//   - while 里 break 只跳出 while，外层 for 继续，
//     最终 rank 一定变成 NUM_RANKS（13），
//     第二个 for 访问 num_in_rank[13]，越界，未定义行为。
//   - 而且第二个 for 的边界检查 `rank < NUM_RANKS` 写在
//     `num_in_rank[rank] > 0` 后面，先访问再检查，顺序反了。
//   原书 poker.c 的 straight 判断是：
//     rank = 0;
//     while (num_in_rank[rank] == 0) rank++;
//     for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
//         num_consec++;
//     if (num_consec == NUM_CARDS) { straight = true; return; }
//
// 错误 3：straight 时没有提前 return。
//   原书在 straight 为真时直接 return，
//   因为 straight 不可能同时有 four/three/pairs。
//   你继续往下检查，结果虽然不会错（straight 时这些必然为假），
//   但多做无用功，逻辑也不如原书清晰。
//
// 错误 4：变量名 num 表示“连续点数个数”，含义不清。
//   建议改成 num_consec，与原书一致。
//
// ============================================================
// * 正确版本（本文件唯一可运行的 main）：
// * 保持你的结构，只修正 analyze_hand；
// * 数组类型改成 int，与原书一致（char 也能用，但 int 更自然）。
// ============================================================

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

bool straight, flush, four, three;
int pairs = 0;

void read_cards(int num_in_rank[], int num_in_suit[]);
void analyze_hand(int num_in_rank[], int num_in_suit[]);
void print_result(void);

int main(void)
{
    while (true) {
        // 每局重新初始化两个数组，清零。
        int num_in_rank[NUM_RANKS] = {0};
        int num_in_suit[NUM_SUITS] = {0};

        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit);
        print_result();
    }
}

void read_cards(int num_in_rank[], int num_in_suit[])
{
    int rank_ch, suit_ch, rank = 0, suit = 0, ch;
    int num = 0;
    bool panduan[NUM_RANKS][NUM_SUITS] = {false};

    while (num < NUM_CARDS) {
        bool bad_card = false;

        printf("Enter a card: ");
        rank_ch = getchar();

        switch (rank_ch) {
            case '0':               exit(EXIT_SUCCESS);
            case '2':   rank = 0;   break;
            case '3':   rank = 1;   break;
            case '4':   rank = 2;   break;
            case '5':   rank = 3;   break;
            case '6':   rank = 4;   break;
            case '7':   rank = 5;   break;
            case '8':   rank = 6;   break;
            case '9':   rank = 7;   break;
            case 't': case 'T': rank = 8;  break;
            case 'j': case 'J': rank = 9;  break;
            case 'q': case 'Q': rank = 10; break;
            case 'k': case 'K': rank = 11; break;
            case 'a': case 'A': rank = 12; break;
            default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default:            bad_card = true;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
            if (ch != ' ')
                bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (panduan[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            panduan[rank][suit] = true;
            num++;
        }
    }
}

void analyze_hand(int num_in_rank[], int num_in_suit[])
{
    int num_consec = 0;
    int rank, suit;

    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    // 同花：某一种花色的牌数是 NUM_CARDS。
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    // 顺子：从第一个非零点数开始，连续非零的点数个数等于 NUM_CARDS。
    rank = 0;
    while (num_in_rank[rank] == 0)
        rank++;
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;

    if (num_consec == NUM_CARDS) {
        straight = true;
        return;   // 顺子不可能同时有四条/三条/对子，直接返回。
    }

    // 四条、三条、对子。
    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4)
            four = true;
        if (num_in_rank[rank] == 3)
            three = true;
        if (num_in_rank[rank] == 2)
            pairs++;
    }
}

void print_result(void)
{
    if (straight && flush)       printf("Straight flush");
    else if (four)               printf("Four of a kind");
    else if (three && pairs == 1) printf("Full house");
    else if (flush)              printf("Flush");
    else if (straight)           printf("Straight");
    else if (three)              printf("Three of a kind");
    else if (pairs == 2)         printf("Two pairs");
    else if (pairs == 1)         printf("Pair");
    else                         printf("High card");

    printf("\n\n");
}

// ============================================================
// 批改总结：
// ============================================================
// ✅ main 把两个数组移到函数内，作为参数传递，符合题目要求。
// ✅ read_cards 逻辑正确：映射、判重、bad_card 处理都没问题。
// ✅ print_result 判断顺序正确。
//
// ❌ analyze_hand 有三处严重错误：
//   1. flush 判断写成了 straight = true，应为 flush = true；
//      条件应为 num_in_suit[i] == NUM_CARDS，不是 == NUM_SUITS。
//   2. straight 判断逻辑错误：第一个 for+while 会让 rank 变成 13，
//      第二个 for 访问 num_in_rank[13] 越界，未定义行为。
//      正确写法：先 while 找第一个非零 rank，再 for 数连续非零个数。
//   3. straight 为真时应提前 return，原书就是这样，
//      避免继续检查 four/three/pairs。
//
// ⚠️ 建议（不是错误）：
//   - 数组类型用 int 比 char 更自然，counts 虽然最大是 5，
//     char 也能存，但原书用 int，保持一致性更好。
//   - 变量 num 改成 num_consec，含义更清楚。
//   - "Duplicat card" 拼写应为 "Duplicate card"。
//
// 你的注释批改：
// - “用自增来标记” ✅ 正确。
// - “用下标当位置，来计算是否重复” ✅ 正确。
// - “只要有一个不对就掉” ✅ 正确，bad_card 一票否决。
// - “这个判断还是留一手” ⚠️ 意图对，但位置放错了，
//   应该先检查 rank < NUM_RANKS 再访问 num_in_rank[rank]。
// ============================================================