#include <stdio.h>

int main(void) {
    char str[100];
    char terminator; // 保存标点符号
    int len = 0;
    int m;

    printf("Enter a sentence: ");
    
    // 1. 吸收整个句子进入一维数组
    while ((m = getchar()) != EOF) {
        if (m == '.' || m == '?' || m == '!') {
            terminator = (char)m; // 把标点存起来
            break;
        }
        str[len++] = (char)m;
    }

    printf("Reversal of sentence: ");
    
    // 2. 物理游标倒车扫描
    int end = len - 1; // 指向句尾最后一个字母的下标(这里没有'\0'，只有初始化时用双引号字符串字面量才有)
    
    // 这里end放在外面，为循环回流寻址提供关键，全靠内部空格断点
    while (end >= 0) {   // <-- 一个个去检索打印(end >=0 是下标界限，只要有它，依据它的计算只要对上就行)
        // 跳过单词末尾的空格
        while (end >= 0 && str[end] == ' ') {
            end--;   // <-- 跳过末尾空格 
        }
        
        // 找这个单词的开头（直到遇到空格或数组开头）
        int start = end;
        while (start >= 0 && str[start] != ' ') {
            start--;  // <-- 最后再自减永远作用于下一次循环
        }
        
        // 打印这个单词（从 start+1 打印到 end）  从头打到尾，以空格做标记，向后去打印，打印到结尾
        for (int i = start + 1; i <= end; i++) {
            putchar(str[i]);
        }
        
        // 只要不是最后一个打印的词，后面就补个空格
        if (start >= 0) {
            putchar(' ');
        }
        
        // 游标跳到上一个单词的末尾
        end = start - 1;
    }

    // 3. 最后打印标点符号
    printf("%c\n", terminator);
    
    return 0;
}
// 倒车回流，空格做标记，标点判断拿，每次一个倒车回流最后补上空格