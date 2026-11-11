// ============================================================
// 第8章 8.1节 interest.c：复利计算表格
// 题目（对应教材 8.1 节）：
//   输入起始利率和年数，显示不同利率下每年末的账户余额。
//   初始余额 100.00，利率从 low_rate 到 low_rate + 4，
//   共 5 档，每档每年按复利增长。
// ============================================================

// * 你的代码（微调：只修正两处拼写，逻辑没动）：
#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
    int i, low_rate, num_years, year;
    double value[5];

    // * 微调：rete → rate
    printf("Enter interest rate: ");
    scanf("%d", &low_rate);

    // * 微调：year → years
    printf("Enter number of years: ");
    scanf("%d", &num_years);

    // * 表头：先输出 "Years"，再输出 5 档利率。
    // * %6d%% 中 %% 输出百分号，宽度 6 对齐。
    printf("\nYears");
    for (i = 0; i < NUM_RATES; i++) {
        printf("%6d%%", low_rate + i);
        value[i] = INITIAL_BALANCE;
    }
    printf("\n");

    // * 逐年计算复利并输出。
    // * value[i] += 利率 * value[i] 等价于
    // * value[i] = value[i] * (1 + 利率)，正确。
    for (year = 1; year <= num_years; year++) {
        printf("%3d    ", year);
        for (i = 0; i < NUM_RATES; i++) {
            value[i] += (low_rate + i) / 100.0 * value[i];
            printf("%7.2f", value[i]);
        }
        printf("\n");
    }

    return 0;
}

// ============================================================
// 批改总结：
// ✅ 完全正确。
//   - NUM_RATES 用 sizeof 计算数组长度，写法标准。
//   - 表头 %6d%% 输出利率和百分号，正确。
//   - value[i] 初始化为 INITIAL_BALANCE，正确。
//   - 复利公式 value[i] += (low_rate + i) / 100.0 * value[i]，
//     等价于 value[i] *= (1 + 利率)，正确。
//   - 输出格式 %7.2f 保留两位小数，与表格对齐，正确。
//   - 外层 year、内层 i 的循环结构正确。
//
// ⚠️ 微调（已在源代码中改）：
//   - "interest rete" → "interest rate"
//   - "number of year" → "number of years"
//   只是提示语拼写，不影响运行结果。
//
// ? 补充：
//   1. NUM_RATES 依赖 value 数组，所以 #define 必须写在
//      value 声明之后（或至少在同一作用域可见）。
//      你的代码把 #define 放在文件开头，value 在 main 里声明，
//      sizeof(value) 在 main 里展开时 value 已可见，所以能编译。
//      这是原书写法，没问题。
//   2. 如果 low_rate 输入 5，num_years 输入 5，
//      输出的是 5%、6%、7%、8%、9% 五档，
//      每年末余额各一列，共 5 行。
// ============================================================