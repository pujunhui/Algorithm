#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED

//采用插入排序思想进行优化
template<typename T>
void __shiftDown(T arr[], int n, int k) {
    T e = arr[k];
    int j = 2 * k + 1; //从k的左子孩子开始往后shiftDown
    while (j < n) {
        if (j + 1 < n && arr[j] < arr[j + 1]) { //判断是否有右孩子，并比较左右孩子的大小
            j++;
        }
        if (e >= arr[j]) {
            break;
        }
        arr[k] = arr[j];
        k = j;
        j = 2 * k + 1;
    }
    arr[k] = e;
}

template<typename T>
void heapSort(T arr[], int n) {
    //Heapify：创建最大堆，从最后一个非叶子节点开始调整
    for (int i = n / 2 - 1; i >= 0; i--) {
        __shiftDown(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); //将最大值依次放到末尾
        __shiftDown(arr, i, 0); //重新维护最大堆
    }
}

#endif // HEAPSORT_H_INCLUDED
