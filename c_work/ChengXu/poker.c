#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/*全局变量，方便各个程序读取*/
int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];
bool straight, flush, four, three;   // 这是判断类型用的
int pairs;  /*能成为0，1，或2*/

/*函数声明*/
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
    bool card_exists[NUM_RANKS][NUM_SUITS];
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;
// 这些执行重复操作的都是局部变量，这样利用生命周期，让每次调用重置
    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++)   // <-- 这个本来就要嵌套循环初始化，这只是顺手的是
            card_exists[rank][suit] = false;
    }
    for (suit = 0; suit < NUM_SUITS; suit++)     // <-- 一次独立循环就行了，嵌套导致重复赋值，过于冗杂
        num_in_suit[suit] = 0;
    
    while (cards_read < NUM_CARDS) {   // <-- 决定取多少次数，cards_read是计数器
        bad_card = false;       // <-- 每一次取数，判断bad_card都是初始化成false
    
    printf("Enter a card: ");

    rank_ch = getchar();     // <-- 拿第一个数
    switch (rank_ch) {
        case '0':       exit(EXIT_SUCCESS); // <-- 0就退出
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
        default:         bad_card = true;    // <-- 只要出错，bad_card为true
    }
    suit_ch = getchar();      // <-- 再拿花色
    switch (suit_ch) {
        case 'c': case 'C': suit = 0; break;
        case 'd': case 'D': suit = 1; break;
        case 'h': case 'H': suit = 2; break;
        case 's': case 'S': suit = 3; break;
        default:            bad_card = true;   // <-- 一样，只要一个不对就掉
    }
    while ((ch = getchar()) != '\n')    // <-- 把所有清空，吃了的同时防止后面再输入别的字(因为换行符是所有的末尾，拿到它等于清空一行)
        if (ch != ' ')  bad_card = true;   // <-- 输入空格都可以接受，后面还有就掉
    
    if (bad_card)
        printf("Bad card; ignored.\n");
    else if (card_exists[rank][suit])     // <-- 这是判断重复，第一轮用不上
        printf("Duplicat card; ignored.\n");
    else {         // <-- 只要是有错误，后面的改变不执行，计数器也不增加，相当于continue
        num_in_rank[rank]++;            // <-- 标记位置，用自增来标记
        num_in_suit[suit]++;
        card_exists[rank][suit] = true;    // <-- 用下标当位置，来计算是否重复
        cards_read++;              // <-- 计数器加一
        }
    }

}
// 这里已经装进去了，整个数组为一牌
// 该函数值判断输入多，输入错的情况，非要作死程序无法进行

void analyze_hand(void)
{
    int num_consec = 0;
    int rank, suit;
/*这些都是全局变量*/
    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;
/*这里的遍历拿对应数字次数比较*/
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)    // <-- 如果5个花色一样
            flush = true;    // <-- 根本不用记录下标，是判断整个数组，如果要，直接break结束就能保留下标

    rank = 0;
    /*这一段考察连续段，我们先跳过0，再去选到0，看看一共执行了多少次*/
    while (num_in_rank[rank] == 0) rank++;    // <-- 选到有值的地方
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)   // <-- 选到没值的地方结束(它们是连续的)(自增下标往下面一直跳)
        num_consec++;         // <-- 选到一次就加
    if (num_consec == NUM_CARDS) {   // <-- 如果5个凑齐就是顺子
        straight = true;
        return;           // <-- 拿到花色和确认的值就可以跑路了
    }

    for (rank = 0; rank < NUM_RANKS; rank++) {      // <-- 开始遍历拿重复的值
        if (num_in_rank[rank] == 4) four = true;   // 这里都是记录
        if (num_in_rank[rank] == 3) three = true;
        if (num_in_rank[rank] == 2) pairs++;    // <-- 看看有几个对子
    }
}

void print_result(void)
{
    /*开始逐步判断条件*/
    if (straight && flush) printf("Straight flush");  // <-- 同花顺
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