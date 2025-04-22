#include <iostream>
#include "SortTestHelper.h"

#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include <algorithm>


using namespace std;

void testSort(int* arr, int n) {
    int* arrs[7];
    int* expect;

    expect = SortTestHelper::copyIntArray(arr, n);
    clock_t startTime = clock();
    std::sort(expect, expect + n);
    clock_t endTime = clock();
    cout << "std::sort" << " : " << double(endTime - startTime) / CLK_TCK << " s" << endl;

    for (int i = 0; i < sizeof(arrs) / sizeof(int*); i++) {
        arrs[i] = SortTestHelper::copyIntArray(arr, n);
    }

    //SortTestHelper::testSort("Bubble Sort", cocktailSort1, arrs[0], n, expect);
    //SortTestHelper::testSort("Selection Sort", selectionSort1, arrs[1], n, expect);
    //SortTestHelper::testSort("Insertion Sort", insertionSort1, arrs[2], n, expect);
    SortTestHelper::testSort("Shell Sort", shellSort, arrs[3], n, expect);
    SortTestHelper::testSort("Merge Sort", mergeSortBU1, arrs[4], n, expect);
    SortTestHelper::testSort("Quick Sort", quickSort3Ways, arrs[5], n, expect);
    SortTestHelper::testSort("Heap Sort", heapSort, arrs[6], n, expect);


    for (int i = 0; i < sizeof(arrs) / sizeof(int*); i++) {
        delete[] arrs[i];
    }
    delete[] expect;
}

int main() {
    int n = 1000000;
    int* arr;

    // 测试1 一般性测试
    cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
    arr = SortTestHelper::generateRandomArray(n, 0, n);
    testSort(arr, n);
    delete[] arr;

    cout << endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;

    cout << "Test for Random Nearly Ordered Array, size = " << n << ", swap time = " << swapTimes << endl;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    testSort(arr, n);
    delete[] arr;

    cout << endl;

    // 测试3 测试存在包含大量相同元素的数组
    cout << "Test for Random Array, size = " << n << ", random range [0,10]" << endl;
    arr = SortTestHelper::generateRandomArray(n, 0, 10);
    testSort(arr, n);
    delete[] arr;

    return 0;
}
