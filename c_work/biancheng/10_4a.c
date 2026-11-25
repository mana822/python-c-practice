// ============================================================
// 第10章 第4题：加入“同花大顺”识别
// 同花大顺 = 同花 + 顺子 + 最小牌是 10（10-J-Q-K-A）
// 级别高于其他所有类别。
//
// 核心就一句：print_result 最前面加一个判断，
// 条件为 straight && flush && hand[0][0] == 10。
// 不需要新增变量，不需要改 analyze_hand，不需要改全局。
// ============================================================

// ------------------------------------------------------------
// * 改动一：analyze_hand 里的 straight 判断保持原样
// ------------------------------------------------------------
// 你原来的 straight 判断已经能识别 10-J-Q-K-A，
// 因为点数映射里 10 是 10，A 是 14，
// 排序后就是 10,11,12,13,14，相邻差 1，straight = true。
// 所以 analyze_hand 不需要动。

// ------------------------------------------------------------
// * 改动二：只在 print_result 最前面加一行
// ------------------------------------------------------------
void print_result(void)
{
    // * 同花大顺：同花 + 顺子 + 最小牌是 10。
    // * 放在最前面，因为它的级别高于其他所有类别。
    if (straight && flush && hand[0][0] == 10)
        printf("Royal flush");

    else if (straight && flush)   printf("Straight flush");
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
// * 为什么这样写就够：
// ============================================================
// 1. hand 本来就是全局数组，print_result 可以直接访问。
// 2. hand 在 analyze_hand 里已经按点数升序排好，
//    所以 hand[0][0] 是最小点数。
// 3. 同花大顺的点数正好是 10,11,12,13,14，
//    最小点数 hand[0][0] 就是 10。
// 4. straight 已经保证是顺子，flush 已经保证是同花，
//    再加 hand[0][0] == 10，三个条件合起来就是同花大顺。
//
// 不需要 dashun 变量，不需要改 analyze_hand，
// 不需要新增全局变量。只加一行判断，改完就能跑。
//
// ============================================================
// * 你原来的 dashun 方案：
// ============================================================
// bool dashun = false;
// for (...) if (...) straight = false;
// if (straight) { if (hand[0][0] == 10) dashun = ture; return; }
//
// 思路是对的，但有三处要修：
// 1. ture → true，拼写错误。
// 2. dashun 如果是局部变量，print_result 访问不到，
//    需要像 straight 一样声明为全局。
// 3. 只判断 hand[0][0] == 10 不够，
//    还要结合 flush，否则非同花的 10-J-Q-K-A 也会被当成同花大顺。
//
// 如果坚持用 dashun，最小改法是：
//   - 全局加一行：bool dashun = false;
//   - analyze_hand 开头加：dashun = false;
//   - straight 为真时：
//       if (flush && hand[0][0] == 10) dashun = true;
//       return;
//   - print_result 最前面：
//       if (dashun) printf("Royal flush");
//
// 但这样要改三个地方。
// 直接在 print_result 加一行判断，只需要改一个地方，
// 更符合“只要加入以下代码即可”的题意。
// ============================================================