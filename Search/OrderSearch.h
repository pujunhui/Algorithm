#pragma once

//顺序查找
template<typename T>
int orderSearch(T arr[], int n, T target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; //查找成功，退出循环
        }
    }
    return -1;
}