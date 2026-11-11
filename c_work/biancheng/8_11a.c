// ============================================================
// 第8章 第11题：电话号码转数字，给输出加标签
// 题目：
//   Enter phone number: 1-800-COL-LECT
//   In numeric form: 1-800-265-5328
//
//   在显示之前，需要把电话号码（原始或数值格式）存进字符数组。
//   假定长度不超过 15 个字符。
// ============================================================

// * 你的代码（已把该改的都改进去，保留你的结构）：
#include <stdio.h>

int main(void)
{
    char list[16] = {};   // * 已改：题目说长度不超过 15，开 16 刚好，
                          //   末尾留一个位置放 '\0'（虽然这里没用到字符串函数，
                          //   但留一位是好习惯）。
    int i = 0;            // * i 是已存入字符的个数。
    int m;                // * 已改：m 用 int 接收 getchar 的返回值。
                          //   getchar 返回 int，因为要能表示 EOF（通常是 -1）。
                          //   用 char 接收，EOF 可能被截断，m != EOF 判断不可靠。
                          // * 已删：原来的 char n 外层声明，因为输出循环里
                          //   另外声明了 int n，外层 n 从未使用，会触发 unused variable 警告。

    printf("Enter phone number: ");

    // * 用 getchar 读普通字符，不是 getwchar。
    // * m 是 int，能正确保存 EOF。
    while ((m = getchar()) != '\n' && m != EOF) {
        list[i] = (char)m;   // * 存入数组时再转成 char，字符本身不会超过 char 范围。
        i++;
    }

    // * 统一转换：下标 0 到 i-1 是有效字符，用 j < i。
    for (int j = 0; j < i; j++) {
        switch (list[j]) {
            case 'A': case 'B': case 'C':
                list[j] = '2'; break;
            case 'D': case 'E': case 'F':
                list[j] = '3'; break;
            case 'G': case 'H': case 'I':
                list[j] = '4'; break;
            case 'J': case 'K': case 'L':
                list[j] = '5'; break;
            case 'M': case 'N': case 'O':
                list[j] = '6'; break;
            case 'P': case 'Q': case 'R': case 'S':
                list[j] = '7'; break;
            case 'T': case 'U': case 'V':
                list[j] = '8'; break;
            case 'W': case 'X': case 'Y': case 'Z':
                list[j] = '9'; break;
            default:
                // * 非字母字符保持不变。
                break;
        }
    }

    printf("In numeric form: ");

    // * 输出数值格式，同样用 n < i。
    for (int n = 0; n < i; n++) {
        printf("%c", list[n]);
    }

    // * 已加：末尾换行，输出更整洁。
    printf("\n");

    return 0;
}

// * 验证：
//   输入 1-800-COL-LECT
//   → In numeric form: 1-800-265-5328  ✅
//
//   输入 CALLATT
//   → In numeric form: 2255288  ✅

// ============================================================
// 批改总结：
// ✅ 逻辑正确：先存数组再统一转换，符合题目“先存储再显示”的要求。
// ✅ switch 映射正确，default 保留非字母字符，输出标签正确。
// ✅ 不需要 toupper，因为第7章第4题已说明输入字母都是大写。
//
// 本次已改进去的修正：
// 1. m 从 char 改成 int，能正确判断 EOF。
// 2. 删掉外层未使用的 char n，避免 unused variable 警告。
// 3. 数组从 100 缩到 16，符合题目“长度不超过 15”的要求。
// 4. 两个循环边界用 j < i、n < i，不会多处理 '\0'。
// 5. 输出末尾补 \n。
//
// ? 你的注释“筛选和存入可以到一起，可以更改调整”正确。
//   可以边读边转换再存入，但题目明确要求“先存入数组再显示”，
//   你现在的结构更贴合题意，不需要改。
// ============================================================