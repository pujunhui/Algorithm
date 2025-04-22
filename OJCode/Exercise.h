#ifndef EXERCISE_H_INCLUDED
#define EXERCISE_H_INCLUDED

#include "SortTestHelper.h"

template<typename T>
int __partition(T arr[], int n) {
    swap(arr[0], arr[rand() % n]);
    T v = arr[0];
    //arr[1...p] < v <= arr(p....n)
    int p = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < v) {
            swap(arr[++p], arr[i]);
        }
    }
    swap(arr[0], arr[p]);
    return p;
}

//查找排名为order的数
template<typename T>
int numberOfOrder(T arr[], int n, int order) {
    srand(time(NULL));
    int f = 15;
    if (n < f && order < f) {
        insertionSort1(arr, n);
        return arr[order];
    }

    int p = __partition(arr, n);
    if (p < order) {
        return numberOfOrder(&arr[p], n - p, order - p);
    }
    else if (p > order) {
        numberOfOrder(arr, p, order);
    }
    else {
        return arr[p];
    }
}

//查找前100名的数

//多路归并排序


#endif // EXERCISE_H_INCLUDED
