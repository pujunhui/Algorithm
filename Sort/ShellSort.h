#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED

//希尔排序是插入排序的一种改进版
// 
// 如何确定最优间隔?
// 原始希尔序列：gap = n/2, n/4, ..., 1（时间复杂度约为O(n²)）。
// 优化序列：如Hibbard序列（2^k-1）、Sedgewick序列（9×4^k-9×2^k+1），可提升至O(n^(4/3))。

template<typename T>
void shellSort(T arr[], int n) {
    int gap = 1; //间隔控制
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < n; i++) { //插入排序
            T e = arr[i];
            int j = i;
            for (; j >= gap && e < arr[j - gap]; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = e;
        }
        gap /= 3;
    }
}

#endif // SHELLSORT_H_INCLUDED
