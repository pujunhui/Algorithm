#ifndef HANOI_H_INCLUDED
#define HANOI_H_INCLUDED

#include<iostream>

using namespace std;

/**
* 汉诺塔
*/

//存在3个柱子a、b、c
//将n个圆盘从起始柱子a移动到目标柱子c
int hanoi(int n, char a, char b, char c) {
    if (n == 0) return 0;
    //将n-1个圆盘从起始柱子a移动到辅助柱子b
    int l = hanoi(n - 1, a, c, b);
    //将最后一个圆盘从起始柱子a移动到目标柱子c
    cout << "Move disk-" << n << " : " << a << " to " << c << endl;
    //将n-1个圆盘从辅助柱子b移动到辅助柱子c
    int r = hanoi(n - 1, b, a, c);
    return l + r + 1;
}

void testHanoi() {
    int n;
    cin >> n;
    cout << hanoi(n, 'A', 'B', 'C');
}

#endif // HANOI_H_INCLUDED
