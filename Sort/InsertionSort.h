#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED

/**
* 插入排序：将未排序元素依次插入到已排序数组中合适的位置，使得插入后的数组依旧保持有序
* 【对于近有序数组，排序效率非常高】
* 
* 效率比冒泡/选择排序好，原因：
*     1、无需遍历整个未排序数组，只需要将新元素插入到已排序数组的合适位置
*/

//原始插入排序，交换相邻元素
template<typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

//改进后的插入排序，移位+插入
template<typename T>
void insertionSort1(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        //将元素arr[i]插入到合适的位置
        T e = arr[i]; //暂存arr[i]
        int j; //保存需要插入的位置索引
        for (j = i; j > 0 && arr[j - 1] > e; j--) { //如果
            arr[j] = arr[j - 1]; //依次覆盖后一个元素
        }
        arr[j] = e;
    }
}

#endif // INSERTIONSORT_H_INCLUDED