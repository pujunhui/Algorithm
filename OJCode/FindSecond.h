#ifndef FINDSECOND_H_INCLUDED
#define FINDSECOND_H_INCLUDED

#include<iostream>

//查找第一和第二大数的位置

void findSecond(int arr[], int l, int r, int& x1, int& x2) {
    //给x1、x2设置一个无效值
    x1 = -1;
    x2 = -1;

    //查找最大元素的索引
    for (int i = l; i < r; i++) {
        if (x1 == -1 || arr[i] > arr[x1]) {
            x1 = i;
        }
    }
    //查找第二大元素的索引
    for (int i = l; i < r; i++) {
        if (i == x1) { //忽略最大元素的位置
            continue;
        }
        if (x2 == -1 || arr[i] > arr[x2]) {
            x2 = i;
        }
    }
}

void findSecond2(int arr[], int l, int r, int& x1, int& x2) {
    x1 = l;
    x2 = l + 1;
    if (arr[x1] < arr[x2]) {
        std::swap(x1, x2);
    }

    for (int i = l + 2; i < r; i++) {
        if (arr[x2] < arr[i]) {
            x2 = i;
            if (arr[x1] < arr[x2]) {
                std::swap(x1, x2);
            }
        }
    }
}

void findSecond3(int arr[], int l, int r, int& x1, int& x2) {
    if (r - l == 2) { //如果只有2个元素
        x1 = l;
        x2 = l + 1;
        if (arr[x1] < arr[x2]) {
            std::swap(x1, x2);
        }
    }
    else if (r - l == 3) { //如果只有3个元素
        if (arr[l] > arr[l + 1]) {
            x1 = l;
            if (arr[l + 1] > arr[l + 2])
                x2 = l + 1;
            else
                x2 = l + 2;
        }
        else {
            x1 = l + 1;
            if (arr[l] > arr[l + 2])
                x2 = l;
            else
                x2 = l + 2;
        }
        if (arr[x1] < arr[x2]) {
            std::swap(x1, x2);
        }
    }
    else {
        int mid = (l + r) >> 1; //将数组一分为二
        int x1L, x2L; findSecond3(arr, l, mid, x1L, x2L); //获取左数组第一第二大元素位置
        int x1R, x2R; findSecond3(arr, mid, r, x1R, x2R); //获取右数组第一第二大元素位置
        if (arr[x1L] > arr[x1R]) {
            x1 = x1L;
            x2 = (arr[x2L] > arr[x1R]) ? x2L : x1R;
        }
        else {
            x1 = x1R;
            x2 = (arr[x1L] > arr[x2R]) ? x1L : x2R;
        }
    }
#endif // FINDSECOND_H_INCLUDED
