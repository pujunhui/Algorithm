#pragma once
#include<iostream>

using namespace std;

/**
* 斐波拉契数列求解
* 斐波那契数列的性质是F(k) = F(k-1) + F(k-2)
*/

//递归版本
int fibonacci(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

//动态规划版本
int fibonacci1(int n)
{
    int x = 1, pre = 0;
    for (int i = 0; i < n; i++) {
        int temp = x;
        x = x + pre;
        pre = temp;
    }
    return x;
}

void testFibonacci() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << fibonacci1(i) << " ";
    }
}