#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED

/**
 * 冒泡排序：相邻元素进行比较和交换，将最大值逐步移至末尾
 * 效率并不高，原因：
 *    1、每次冒泡都需要遍历未排序整个数组
 *    2、存在大量的相邻元素交换
 */

// 最原始的冒泡排序
template <typename T>
void bubbleSort(T arr[], int n) {
    // n-1次冒泡(最后1次自然有序)
    for (int i = 0; i < n - 1; i++) {
        // 每次冒泡，相邻两个元素进行比较，将当前数组中最大元素移至末尾
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 改进后的冒泡排序一
// 由于冒泡排序采用相邻元素进行比较和交换，如果某次冒泡，未出现交换，则表示数组已经有序
template <typename T>
void bubbleSort1(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool isSwap = false;  // 记录本次遍历是否发生过交换
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                isSwap = true;
            }
        }
        if (!isSwap) {
            break;
        }
    }
}

// 改进后的冒泡排序二
template <typename T>
void bubbleSort2(T arr[], int n) {
    int lastSwapPos = n - 1;  // 记录最后一次交换的位置,意味着后面的数组已经有序
    int tempPos;
    do {
        tempPos = lastSwapPos;
        lastSwapPos = 0;
        for (int j = 0; j < tempPos; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                lastSwapPos = j;
            }
        }
    } while (lastSwapPos > 0);
}

// 鸡尾酒排序(双向冒泡排序)
template <typename T>
void cocktailSort(T arr[], int n) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
        right--;
        for (int j = right; j > left; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            }
        }
        left++;
    }
}

// 改进鸡尾酒排序
template <typename T>
void cocktailSort1(T arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapPos = left;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapPos = i;  // 此时记录向右冒泡最后一次交换位置
            }
        }
        right = swapPos;  // 将最后一次交换位置作为右冒泡起点
        for (int j = right; j > left; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                swapPos = j;  // 此时记录向左冒泡最后一次交换位置
            }
        }
        left = swapPos;  // 将最后一次交换位置作为左冒泡起点
    }
}

#endif  // BUBBLESORT_H_INCLUDED
