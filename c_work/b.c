#include <stdio.h>

int main(void)
{
    int N, p, q; 
    scanf("%d", &N);
    
    // 1. 外层循环：p 从 3 开始，每次 +2（只找奇数）。p <= N/2 保证 p 是最小的
    for (p = 3; p <= N / 2; p += 2) {
        int a = 0; 
        q = N - p;
        
        // 2. 判断 p 是不是素数。用 j 做循环变量，只要测到 j*j <= p 就行
        for (int j = 2; j * j <= p; j++) {
            if (p % j == 0) { a = 1; break; }
        }
        if (a) continue; // p 不是素数，直接试下一个
        
        // 3. 判断 q 是不是素数。用 k 做循环变量
        for (int k = 2; k * k <= q; k++) {
            if (q % k == 0) { a = 1; break; }
        }
        if (a) continue; // q 不是素数，直接试下一个
        
        // 4. 都过了，输出并结束
        printf("%d = %d + %d\n", N, p, q);
        break;
    }

    return 0;
}