// ============================================================
// 第10章 第7题：用字符模拟七段显示器（保留无参数 print 版本）
// 题目要求的三个函数原型：
//   void clear_digits_array(void);
//   void process_digit(int digit, int position);
//   void print_digits_array(void);
//
// 三个函数都不带参数，所以位数只能通过全局变量传递。
// 你用全局 w 是对的，保留。
// ============================================================

// ! 你的原始代码（整段注释，你的笔记用 / 保留，批改见下方）：
/*
#include <stdio.h>
#define MAX_DIGITS 10
int w;
void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);
const int segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, //8
    {1 ,1 ,1 ,0 ,0 ,1 ,1}   //9
};
int num[MAX_DIGITS] = {0};
int digits[3][40] = {{[0 ... 39] = ' '}, {[0 ... 39] = ' '}, {[0 ... 39] = ' '}}; // 初始化为 ' '

void clear_digits_array(void)
{
    int m;
    w = 0;
    while ((m = getchar()) != EOF && m != '\n' && w < MAX_DIGITS) {    // 终止符是'\n'，要什么内部卫语句筛选
        if (m >= '0' && m <= '9' ) {
        num[w] = m - '0';
        w++;
        }
    }
}
void process_digit(int digit, int position)
{
    int col = position * 4; // 每个数字占据 4 列（3 列数字 + 1 列空格）
    for (int i = 0; i < 7; i++) {
        if (segments[digit][i]) {
            switch (i) {
                case 0: // Top segment
                    digits[0][col + 1] = '_';
                    break;
                case 1: // Top-right segment
                    digits[1][col + 2] = '|';
                    break;
                case 2: // Bottom-right segment
                    digits[2][col + 2] = '|';
                    break;
                case 3: // Bottom segment
                    digits[2][col + 1] = '_';
                    break;
                case 4: // Bottom-left segment
                    digits[2][col] = '|';
                    break;
                case 5: // Top-left segment
                    digits[1][col] = '|';
                    break;
                case 6: // Middle segment
                    digits[1][col + 1] = '_';
                    break;
            }
        }
    }
}
void print_digits_array(void)
{
    for (int m = 0; m < 3; m++) {
        for (int j = 0; j < w * 4; j++) {
            putchar(digits[m][j]);
        }
        putchar('\n');
    }
}
int main(void)
{
    printf("Enter a number: ");
    clear_digits_array();
    for (int i = 0; i < w; i++) {
        process_digit(num[i], i);
    }
    print_digits_array();
    return 0;
}
*/

// ============================================================
// * 批改：
// ============================================================
// ✅ 保留的部分（对的）：
//   - segments 数组内容正确，0~9 编码无误。
//   - process_digit 的段映射正确，col = position*4 正确。
//   - print_digits_array 按行打印 w*4 列，正确。
//   - 用全局 w 记录位数，与“print_digits_array 不接受参数”的题目要求一致。
//   - main 里先 clear、再逐位 process、最后 print，流程正确。
//   - 你注释“终止符是 '\n'”正确。
//
// ❌ 错误 1：clear_digits_array 的职责不符合题目。
//   题目原文：“clear_digits_array 函数在 digits 数组的所有元素中
//   存储空白字符。”
//   它的唯一职责是清空 digits，不负责读输入。
//   你把它当成“读输入 + 存 num 数组 + 统计 w”的函数了，
//   而真正的 digits 清空是靠全局初始化完成的。
//   后果：如果 clear_digits_array 被调用第二次，digits 不会重新清空，
//   会保留上一次的图案。
//   修正：读取输入的逻辑移到 main，clear_digits_array 只清空。
//
// ❌ 错误 2：digits 数组类型用了 int。
//   它存的是字符（'_'、'|'、' '），用 char 更自然、更省内存。
//   putchar 接收 int，char 会隐式提升，输出不受影响。
//   修正：int digits[3][40] → char digits[3][MAX_DIGITS*4]。
//   顺便把 40 换成 MAX_DIGITS*4，与宏绑定，改 MAX_DIGITS 时不用改这里。
//
// ❌ 错误 3：全局初始化用了 GCC 范围指定初始化器 [0 ... 39]。
//   这是 GCC 扩展，不是标准 C23 语法，换编译器会失败。
//   修正：改用循环在 clear_digits_array 里初始化，
//   这样既符合标准，又让 clear_digits_array 真正承担“清空”职责。
//
// ⚠️ 警告 1：num 数组全局声明，其实可以不保留。
//   保留的好处：main 里先全部读完，再统一 process，结构清晰。
//   去掉的好处：边读边 process，少一个全局数组。
//   两种都能跑，这里保留 num 数组，结构与你原代码一致。
//
// ⚠️ 警告 2：print_digits_array 打印 w*4 列。
//   如果 w=0（没输入数字），会打印三行空行。
//   题目示例不会出现，可以加一个 w==0 直接返回的保护。
//   这里加上了，不影响正常输出。
//
// ============================================================
// * 正确版本（本文件唯一可运行的 main）：
// * 保留你的全局 w、num、digits 结构；
// * clear_digits_array 改成只清空 digits；
// * 读取输入移到 main；
// * digits 改成 char；
// * 用循环清空代替 [0 ... 39]。
// ============================================================

#include <stdio.h>

#define MAX_DIGITS 10

// 七段编码：0~9 对应 a,b,c,d,e,f,g 七段。
// 与你的原数组完全相同，没改。
const int segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
};

// 改动 2：int → char；40 → MAX_DIGITS*4。
// 理由：存的是字符，char 更自然；用宏绑定列数，改 MAX_DIGITS 时不用改这里。
char digits[3][MAX_DIGITS * 4];

// 保留全局 w 和 num。
// 理由：题目要求三个函数都不带参数，位数只能通过全局变量传递。
// w 记录已读入的数字个数，num 暂存每位数字。
int w;
int num[MAX_DIGITS];

void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);

int main(void)
{
    int m;

    printf("Enter a number: ");

    // 改动 1 的一半：读取输入从 clear_digits_array 挪到 main。
    // 理由：题目规定 clear_digits_array 只负责清空 digits。
    w = 0;
    while ((m = getchar()) != EOF && m != '\n' && w < MAX_DIGITS) {
        if (m >= '0' && m <= '9') {
            num[w] = m - '0';
            w++;
        }
    }

    // 改动 1 的另一半：clear_digits_array 现在真正做“清空”这件事。
    clear_digits_array();

    for (int i = 0; i < w; i++) {
        process_digit(num[i], i);
    }

    print_digits_array();
    return 0;
}

// 改动 1：clear_digits_array 只清空 digits，不再读输入。
// 改动 3：用双层循环清空，代替 GCC 扩展 [0 ... 39]。
void clear_digits_array(void)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < MAX_DIGITS * 4; c++)
            digits[r][c] = ' ';
}

// 没改：段映射、col 偏移与你原代码完全一致。
void process_digit(int digit, int position)
{
    int col = position * 4;   // 每个数字占 4 列（3 列图案 + 1 列间隔）

    for (int i = 0; i < 7; i++) {
        if (!segments[digit][i])
            continue;

        switch (i) {
            case 0: digits[0][col + 1] = '_'; break; // 顶部
            case 1: digits[1][col + 2] = '|'; break; // 右上
            case 2: digits[2][col + 2] = '|'; break; // 右下
            case 3: digits[2][col + 1] = '_'; break; // 底部
            case 4: digits[2][col]     = '|'; break; // 左下
            case 5: digits[1][col]     = '|'; break; // 左上
            case 6: digits[1][col + 1] = '_'; break; // 中间
        }
    }
}

// 没改：用全局 w 决定打印列数，符合“print_digits_array 不带参数”的题目要求。
// 新增：w == 0 时直接返回，避免打印三行空行。
void print_digits_array(void)
{
    if (w == 0)
        return;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < w * 4; c++)
            putchar(digits[r][c]);
        putchar('\n');
    }
}

// ============================================================
// * 与你的原代码相比，一共改了 4 处，逐条说明：
// ============================================================
// 改动 1：读取输入从 clear_digits_array 移到 main；
//         clear_digits_array 只负责清空 digits。
//   原因：题目原文规定 clear_digits_array 是“在 digits 数组所有元素中
//         存储空白字符”，不是读输入。如果它既读输入又清空，
//         第二次调用时 digits 不会重新清空，会保留上次图案。
//
// 改动 2：digits 类型 int → char，列数 40 → MAX_DIGITS*4。
//   原因：存的是字符，char 更自然、省内存；用宏绑定列数，
//         修改 MAX_DIGITS 时不用同步改 40。
//
// 改动 3：初始化 [0 ... 39] → 双层循环。
//   原因：[0 ... 39] 是 GCC 范围指定初始化器，不是标准 C23 语法，
//         换编译器会编译失败。用循环既标准，又把“清空”逻辑放进
//         clear_digits_array，职责更正确。
//
// 改动 4：print_digits_array 开头加 w == 0 直接返回。
//   原因：没输入数字时，原代码会打印三行空行。
//         加上保护，w==0 时什么也不打印，更干净。
//
// 保留未改的部分：
//   - 全局 w 和 num：题目要求三个函数不带参数，位数只能走全局变量，
//     你的 w 写法是对的。
//   - process_digit 的段映射和 col 偏移：完全正确。
//   - print_digits_array 用 w*4 决定打印列数：与无参数原型一致。
//   - segments 数组内容：完全正确。
//
// ============================================================
// * 验证：
// ============================================================
// 输入 491-9014
//   '-' 不是数字，被忽略，实际处理 4 9 1 9 0 1 4 共 7 位。
//   输出 3 行七段图案，与题目示例一致。
//
// 输入 1234567890123（超过 10 位）
//   while 条件 w < MAX_DIGITS 保证最多存 10 位，多余忽略。
//
// 输入 空行
//   w == 0，print_digits_array 直接返回，不打印空行。
// ============================================================