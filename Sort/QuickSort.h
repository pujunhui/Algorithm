#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include "InsertionSort.h"

/**
* 快速排序：
*
* 归并排序的核心在于"并"：
*    如何将2个有序数组合并在一起。
*    对于"分"，只是简单的将数组一分为二。
*
* 而快速排序的核心在于"分"：
*    找到一个元素，将数组分成2部分，要求满足左数组都小于该元素，右数组都大于该元素。
*    由于左数组都小于右数组，所以无需"并"操作。
*    如果2个数组大小差距过大，快速排序执行效率可能会退化为O(n^2)
*/

///*********************************************

//对arr[l....r)部分进行partition操作
//返回p，使得 arr[l...p) < arr[p] <= arr[p+1...r)
template<typename T>
int __partition(T arr[], int l, int r) {
    //优化二：防止arr为近顺序序列，快速排序将退化为O(n^2)
    swap(arr[l], arr[rand() % (r - l) + l]);
    T v = arr[l];
    //arr[l+1...p] < v <= arr(p....r)
    int p = l;
    for (int i = l + 1; i < r; i++) {
        if (arr[i] < v) {
            swap(arr[++p], arr[i]);
        }
    }
    swap(arr[l], arr[p]);
    return p;
}

//对arr[l....r)部分进行排序
template<typename T>
void __quickSort(T arr[], int l, int r) {
    //if(r - l <= 1) //只有一个元素时，无需排序
    //   return;

    //优化一：当元素较少时，采用插入排序
    if (r - l < 16) {
        insertionSort1(&arr[l], r - l);
        return;
    }
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p);
    __quickSort(arr, p + 1, r);
}

//普通快速排序
template<typename T>
void quickSort(T arr[], int n) {
    srand(time(NULL));
    __quickSort(arr, 0, n);
}

///********************************************

//二路快速排序法
//改进partition算法，解决在大量重复元素情况下，一边数组远大于另一数组的情况
template<typename T>
int __partition2Ways(T arr[], int l, int r) {
    swap(arr[l], arr[rand() % (r - l) + l]);
    T v = arr[l];
    //arr[l+1...i) <= v; arr(j...r) >= v
    int i = l + 1, j = r - 1;
    while (true) {
        //首先从左到右找到大于等于v的元素
        while (i < r && arr[i] < v) i++; //这里不能换成arr[i] <= v，如果arr[l+1...r)=v，则左边的数组会远大于右边
        //然后从右到左找到小于等于v的元素
        while (j > l && arr[j] > v) j--; //这里不能换成arr[j] >= v，如果arr[l+1]>v，aar[l+2...r)=v，则左边的数组会远小于右边
        if (i >= j) break;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);
    return j;
}

//对arr[l....r)部分进行排序
template<typename T>
void __quickSort2Ways(T arr[], int l, int r) {
    //if(r - l <= 1) //只有一个元素时，无需排序
    //   return;

    //优化一：当元素较少时，采用插入排序
    if (r - l < 16) {
        insertionSort1(&arr[l], r - l);
        return;
    }
    int p = __partition2Ways(arr, l, r);
    __quickSort2Ways(arr, l, p);
    __quickSort2Ways(arr, p + 1, r);
}

//二路快速排序
template<typename T>
void quickSort2Ways(T arr[], int n) {
    srand(time(NULL));
    __quickSort2Ways(arr, 0, n);
}

///********************************************

//对arr[l....r)部分进行排序
template<typename T>
void __quickSort3Ways(T arr[], int l, int r) {
    //if(r - l <= 1) //只有一个元素时，无需排序
    //   return;

    //优化一：当元素较少时，采用插入排序
    if (r - l < 16) {
        insertionSort1(&arr[l], r - l);
        return;
    }
    //partition
    swap(arr[l], arr[rand() % (r - l) + l]);
    T v = arr[l];

    int lt = l; //arr[l+1...lt] < v
    int gt = r; //arr[gt...r) > v
    int i = l + 1; //arr[lt+1...i] == v
    while (i < gt) {
        if (arr[i] < v) {
            swap(arr[i], arr[++lt]);
            i++;
        }
        else if (arr[i] > v) {
            swap(arr[i], arr[--gt]);
            //由于交换到位置i的值并不能保证其大小，故i不能自增，需要重新判定
            //i++;
        }
        else { //arr[i] == v
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    __quickSort3Ways(arr, l, lt);
    __quickSort3Ways(arr, gt, r);
}

//三路快速排序
template<typename T>
void quickSort3Ways(T arr[], int n) {
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n);
}

#endif // QUICKSORT_H_INCLUDED
