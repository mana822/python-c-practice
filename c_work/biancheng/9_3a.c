// 3. 修改第 8 章的编程题 9，使其包含下列函数：
// void generate_random_walk(char walk[10][10]);
// void print_array(char walk[10][10]);
// main 函数首先调用 generate_random_walk，该函数把所有数组元素都初始化为字符 '.'，
// 然后将其中一些字符替换为 A~Z 的字母，详见原题的描述。接着，main 函数调用 print_array 函数来显示数组。

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void generate_random_walk(char walk[10][10]);
void print_array(char walk[10][10]);
int main(void)
{
    char walk[10][10];
    srand((unsigned) time(NULL));
    generate_random_walk(walk);
    print_array(walk);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf("%c ", walk[i][j]);
        printf("\n");
    }
    return 0;

}

void generate_random_walk(char walk[10][10])
{
    for (int i = 0; i < 10; i++)
        for (int n = 0; n < 10; n++)
            walk[i][n] = '.';
}

void print_array(char walk[10][10])
{
    int n = 0, m = 0, i, count[4], count1[4] = {1, -1, 0, 0}, count2[4] = {0, 0, 1, -1};
    char ch;
    int j;
    walk[n][m] = 'A';
    for (ch = 'B'; ch <= 'Z'; ch++) {
        i = 0;
        for (j = 0; j < 4; j++) {
            int nn = n + count1[j];
            int nm = m + count2[j];
            if (nn >= 0 && nn <= 9 && nm >= 0 && nn <= 9 && walk[nn][nm] == '.') {
                count[i++] = j;
            }
        }
            if (i == 0) break;
            j = count[rand() % i];
            n += count1[j];
            m += count2[j];
            walk[n][m] = ch;   
    }

}