#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "InsertionSort.h"

/**
* 归并排序：将一个数组分为左右2部分，并分别进行排序，然后再合并成一个新的有序数组。
* 时间复杂的：Nlog(N)，其中log(N)为二分法的时间复杂度，前面的N是归并的时间复杂度。
*/

template<typename T>
void __merge(T arr[], int l, int mid, int r) {
    T* aux = new T[r - l];

    for (int i = l; i < r; i++) { //复制数据
        aux[i - l] = arr[i];
    }

    int i = l, j = mid;
    for (int k = l; k < r; k++) {
        if (i >= mid) {//左子数组已归并结束，将右子数组剩余部分直接copy进归并数组即可完成归并
            //由于右子数组剩余部分与归并数组剩余空间中的内容一致，可以省略copy步骤
            //arr[k] = aux[j - l];
            //j++;
            break;
        }
        else if (j >= r) {//右子数组已归并结束，将左子数组剩余部分直接copy进归并数组即可完成归并
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }
        else {
            arr[k] = aux[j - l];
            j++;
        }
    }
    delete[] aux;
}

//递归使用归并排序，对arr[l...r)的范围进行排序
template<typename T>
void __mergeSort(T arr[], int l, int r) {
    //if(r - l <= 1) //只有一个元素时，无需排序
    //   return;

    //优化二：当元素较少时，采用插入排序
    if (r - l < 16) {
        insertionSort1(&arr[l], r - l);
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid, r);

    //优化一：如果左半部分最后一个数<=右半部分第一个数，就不需要进行合并
    if (arr[mid - 1] > arr[mid]) {
        __merge(arr, l, mid, r);
    }
}

//自顶向下,递归实现
template<typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n);
}

template<typename T>
void __merge1(T arr[], int l, int mid, int r, T aux[]) {
    for (int i = l; i < r; i++) { //复制数据
        aux[i] = arr[i];
    }

    int i = l, j = mid;
    for (int k = l; k < r; k++) {
        if (i >= mid) {
            //arr[k] = aux[j];
            //j++;
            break;
        }
        else if (j >= r) {
            arr[k] = aux[i];
            i++;
        }
        else if (aux[i] < aux[j]) {
            arr[k] = aux[i];
            i++;
        }
        else {
            arr[k] = aux[j];
            j++;
        }
    }
}

template<typename T>
void __mergeSort1(T arr[], int l, int r, T aux[]) {
    //if(r - l <= 1) //只有一个元素时，无需排序
    //   return;

    //优化二：当元素较少时，采用插入排序
    if (r - l < 16) {
        insertionSort1(&arr[l], r - l);
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort1(arr, l, mid, aux);
    __mergeSort1(arr, mid, r, aux);

    //优化一：如果左半部分最后一个数<=右半部分第一个数，就不需要进行合并
    if (arr[mid - 1] > arr[mid]) {
        __merge1(arr, l, mid, r, aux);
    }
}

//改进后的归并排序，不用频繁分配内存空间
template<typename T>
void mergeSort1(T arr[], int n) {
    T* aux = new T[n];
    __mergeSort1(arr, 0, n, aux);
    delete[] aux;
}

//自底向上,迭代实现
template<typename T>
void mergeSortBU(T arr[], int n) {
    // 对于小数组, 使用插入排序优化
    for (int i = 0; i < n; i += 16) {
        insertionSort1(&arr[i], min(i + 16, n) - i);
    }

    for (int gap = 16; gap <= n; gap += gap) { //每次gap增加一倍
        for (int i = 0; i + gap < n; i += (gap + gap)) { //2个gap为一组进行归并
            if (arr[i + gap - 1] > arr[i + gap]) {
                __merge(arr, i, i + gap, min(i + gap + gap, n));
            }
        }
    }
}

//自底向上优化，直接开辟辅助内存
template<typename T>
void mergeSortBU1(T arr[], int n) {
    // 对于小数组, 使用插入排序优化
    for (int i = 0; i < n; i += 16) {
        insertionSort1(&arr[i], min(i + 16, n) - i);
    }

    // 一次性申请aux空间, 并将这个辅助空间以参数形式传递给完成归并排序的各个子函数
    T* aux = new T[n];
    for (int gap = 16; gap <= n; gap += gap) { //每次gap增加一倍
        for (int i = 0; i + gap < n; i += (gap + gap)) { //2个gap为一组进行归并
            if (arr[i + gap - 1] > arr[i + gap]) {
                __merge1(arr, i, i + gap, min(i + gap + gap, n), aux);
            }
        }
    }
    delete[] aux; // 使用C++, new出来的空间不要忘记释放掉:)
}

#endif // MERGESORT_H_INCLUDED
