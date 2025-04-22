#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

/**
* 选择排序：从数组中找到最小元素，放到第一位；然后找到第二小元素，放到第二位......
* 效率不高，但比冒泡排序要好，原因：
*     1、每次都需要遍历整个未排序数组
*     2、每次遍历只做一次元素交换（冒泡排序存在大量相邻元素交换）
*/

//最原始的选择排序
//每次遍历找到最小的值的索引，然后进行交换
template<typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        //寻找[i,n)区间里的最小值
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        //将最小值放到对应位置
        swap(arr[i], arr[minIndex]);
    }
}

//改进后的选择排序
//在每次遍历时, 同时找到当前未处理元素的最大值和最小值
template<typename T>
void selectionSort1(T arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int minIndex = left;
        int maxIndex = right;

        // 在每一轮查找时, 要保证arr[minIndex] <= arr[maxIndex]
        if (arr[minIndex] > arr[maxIndex]) {
            swap(arr[minIndex], arr[maxIndex]);
        }

        for (int i = left + 1; i < right; i++) {
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
            else if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }

        swap(arr[left], arr[minIndex]);
        swap(arr[right], arr[maxIndex]);

        left++;
        right--;
    }
}

#endif // SELECTIONSORT_H_INCLUDED
