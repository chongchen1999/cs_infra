// main.c - 演示ABI概念的简单C程序
#include <stdio.h>

// 一个接收四个参数的函数，展示参数传递
int calculate(int a, int b, float c, double d) {
    int result = a + b + (int)c + (int)d;
    return result;
}

int main() {
    int a = 10;
    int b = 20;
    float c = 15.5f;
    double d = 25.75;

    int result = calculate(a, b, c, d);

    printf("计算结果: %d\n", result);

    return 0;
}