#include <stdio.h>
#include <ctype.h> // 🚨 包含这个头文件

int main(void)
{
    int j, m, i = 0;
    int list[26] = {0};  // 26个坑位，全填0
    
    printf("Enter first word: ");
    while ((j = getchar()) != '\n' && j != EOF) {
        // 🚨 物理过滤1：isalpha 判断是不是字母（大写或小写都返回真）
        if (isalpha((unsigned char)j)) {    // <-- isalpha(读取int型)查询(查表是否为字母，如果是返回非0整数，不是或EOF返回0，所以用来判断)[注意，负数查表同样越界]
            // 🚨 物理过滤2：tolower 把大写转小写（记得强转防负数越界）
            j = tolower((unsigned char)j);  // <-- 转小写，toupper兄弟识别int返回int但只能限于unsigned char  (本质上是查表，如果是负数就越界)
            list[j - 'a']++; // 现在 j 绝对是小写字母，j - 'a' 绝对在 0~25 之间
        }
    }
    
    printf("Enter second word: ");
    while ((m = getchar()) != '\n' && m != EOF) {
        if (isalpha((unsigned char)m)) {
            m = tolower((unsigned char)m);
            list[m - 'a']--; 
        }
    }
    
    // 🚨 终极审判：Fail-Fast
    int is_anagram = 1; // 先假设它是
    for (int i = 0; i < 26; i++) {
        if (list[i] != 0) {
            is_anagram = 0; // 只要有一个不为0，直接推翻假设
            break;          // 物理刹车，后面的不用看了
        }
    }
    
    if (is_anagram) printf("The words are anagrams.\n");
    else printf("The words are not anagrams.\n");
    
    return 0;
}