// ============================================================
// 第9章 第8题：掷骰子游戏（roll_dice + play_game + main）
// 题目：
//   第一次掷：7 或 11 赢；2、3、12 输；其他为“目标”，继续。
//   后续：掷出目标赢，掷出 7 输，其他继续。
//   每局结束问是否再玩，输入不是 y 或 Y 就显示胜败次数并退出。
// ============================================================

// ! 你的原始代码（整段注释，你的笔记用 / 保留，批改见下方）：
/*
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
int roll_dice(void);
bool play_game(void);

int a1, a2, sum;
int main(void)
{
    int f = 0, t = 0;
    char ch;
    srand((unsigned) time(NULL));
    do {
        if (play_game()) t++;
        else f++;
        printf("\nPlay again? ");
        scanf(" %c", &ch);   / <-- %c前面一定加空格，把空白字符吃了，不然你的提交'\n'被拿走了
        printf("\n");
    } while (ch == 'y');
    printf("Wins: %d  Losses: %d", t, f);
    return 0;


}

int roll_dice(void)
{
    a1 = rand() % 6;    / <-- 其实可以直接写成 a1 = rand() % 6 + 1这样也可以
    if (a1 == 0) a1 = 6;
    a2 = rand() % 6;
    if (a2 == 0) a2 = 6;
    sum = a1 + a2;
    return sum;
}

bool play_game(void)   / <-- 一个个都不接受形参，只能用全局变量了(可以调用roll_dice()用变量接住也可以)
{
        roll_dice();
        if (sum == 7 || sum == 11) {printf("You rolled: %d\nYou win!\n", sum); return true;}
        else if (sum == 2 || sum == 3 || sum == 12) {printf("You rolled: %d\nYou lose!\n", sum); return false;}
        else {
            printf("You rolled: %d\nYour point is %d\n", sum, sum);
            int n = sum;
            do {roll_dice();
                printf("You rolled: %d\n", sum);
                } while (sum != 7 && sum != n);

            if (sum == n) {printf("You win!\n"); return true;}
            else {printf("You lose!\n"); return false;}
            }
}
*/

// ============================================================
// * 对你笔记的批改：
// ============================================================
// 1. “%c 前面一定加空格，把空白字符吃了，不然你的提交 '\n' 被拿走了”
//    ✅ 完全正确。scanf(" %c", &ch) 里的空格会跳过前导空白，
//    包括上一轮输入残留的换行符。
//
// 2. “其实可以直接写成 a1 = rand() % 6 + 1 这样也可以”
//    ✅ 完全正确。rand() % 6 + 1 直接得到 1~6，
//    比“取模后判断 0 改 6”更简洁。你当时已经想到了更好的写法。
//
// 3. “一个个都不接受形参，只能用全局变量了（可以调用 roll_dice() 用变量接住也可以）”
//    ⚠️ 前半句是无奈，后半句才是正解。
//    roll_dice 有返回值，play_game 里直接：
//      int sum = roll_dice();
//    就能拿到点数，不需要全局变量。
//    你自己已经写出了更好的办法，只是没改。
//
// ============================================================
// * 代码错误：
// ============================================================
// ❌ while (ch == 'y') 漏了 'Y'。
//    题目要求“不是 y 或 Y 才终止”，输入 Y 也要继续。
//    应改为：while (ch == 'y' || ch == 'Y');
//
// ⚠️ 全局变量 a1、a2、sum 不是错误，但结构上可以更干净。
//    roll_dice 已有返回值，play_game 里直接接住即可。
//
// ⚠️ printf("Wins: %d  Losses: %d", t, f) 末尾缺 \n，建议补上。
//
// ✅ 游戏逻辑完全正确：
//    第一次 7/11 赢、2/3/12 输，其他记为目标；
//    后续掷出目标赢、掷出 7 输，其他继续；
//    do-while 条件 sum != 7 && sum != n 正确；
//    循环结束用 sum == n 判断胜负，正确。
//
// ============================================================
// * 正确版本（本文件唯一可运行的 main）：
// ============================================================

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int roll_dice(void);
bool play_game(void);

int main(void)
{
    int wins = 0, losses = 0;
    char ch;

    srand((unsigned)time(NULL));

    do {
        if (play_game())
            wins++;
        else
            losses++;

        printf("\nPlay again? ");
        scanf(" %c", &ch);
        printf("\n");
    } while (ch == 'y' || ch == 'Y');   // 修正：小写和大写都继续

    printf("Wins: %d  Losses: %d\n", wins, losses);

    return 0;
}

int roll_dice(void)
{
    // 直接 rand() % 6 + 1，得到 1~6。
    int d1 = rand() % 6 + 1;
    int d2 = rand() % 6 + 1;
    return d1 + d2;
}

bool play_game(void)
{
    // 用返回值接住点数，不需要全局变量。
    int sum = roll_dice();
    printf("You rolled: %d\n", sum);

    if (sum == 7 || sum == 11) {
        printf("You win!\n");
        return true;
    }
    if (sum == 2 || sum == 3 || sum == 12) {
        printf("You lose!\n");
        return false;
    }
// 因为有return隔断，所以不需要判断了
    int point = sum;
    printf("Your point is %d\n", point);

    while (1) {
        sum = roll_dice();
        printf("You rolled: %d\n", sum);

        if (sum == point) {
            printf("You win!\n");
            return true;
        }
        if (sum == 7) {
            printf("You lose!\n");
            return false;
        }
    }
}
// 循环判断语句有达成条件就return的，可以不用太麻烦的搞什么条件判断

// ============================================================
// 批改总结：
// ============================================================
// ✅ 游戏逻辑完全正确，第一次判定、目标点、后续循环、胜负判断都无误。
// ✅ scanf(" %c", &ch) 前面的空格处理正确。
// ✅ srand 初始化正确。
//
// ❌ 错误：while (ch == 'y') 漏了 'Y'。
//    题目要求“不是 y 或 Y 才终止”，应改为 ch == 'y' || ch == 'Y'。
//
// ⚠️ 建议：roll_dice 已有返回值，play_game 里直接 int sum = roll_dice(); 即可，
//    不需要全局变量。你自己的注释里也写了这一点。
// ⚠️ printf 末尾建议加 \n。
//
// 你的笔记全部正确：
// - scanf(" %c") 前的空格吃换行，对。
// - rand() % 6 + 1 更直接，对。
// - “可以调用 roll_dice() 用变量接住”，对，只是当时没用。
// ============================================================