#ifndef INVERSIONS_H_INCLUDED
#define INVERSIONS_H_INCLUDED

#include "SortTestHelper.h"
#include<algorithm>

/**
* 使用归并排序思路求解逆序数
*/

template<typename T>
int __mergea(T arr[], int l, int mid, int r) {
    int a_len = mid - l;
    int b_len = r - mid;
    T* a = SortTestHelper::copyIntArray(&arr[l], a_len);
    T* b = SortTestHelper::copyIntArray(&arr[mid], b_len);
    std::sort(a, a + a_len);
    std::sort(b, b + b_len);

    int num = 0;

    if (a[0] > b[b_len - 1]) {
        num = a_len * b_len;
    }
    else if (a[a_len - 1] <= b[0]) {
        num = 0;
    }
    else {
        int i = 0, j = 0;
        while (i < a_len && j < b_len) {
            if (a[i] > b[j]) {
                num += (a_len - i);
                j++;
            }
            else {
                i++;
            }
        }
    }

    delete[] a;
    delete[] b;
    return num;
}
//将左右子数组进行替换
template<typename T>
void __inv(T arr[], int l, int mid, int r) {
    int l_len = mid - l;//左子数组长度
    T* temp = SortTestHelper::copyIntArray(&arr[l], l_len);
    copy(arr + mid, arr + r, arr + l);
    copy(temp, temp + l_len, arr + (r - l_len));
    delete[] temp;
}

template<typename T>
int __mergeb(T arr[], int l, int mid, int r) {
    //对于数组arr，其[l,mid)和[mid,r)内的子数组已有序
    //然后分情况讨论

    ///情况1:[l,r)范围内数组都有序
    if (arr[mid - 1] <= arr[mid])
        return 0;

    ///情况2:[l,mid)全部大于[mid,r)
    if (arr[l] > arr[r - 1]) {
        __inv(arr, l, mid, r);
        return (mid - l) * (r - mid);
    }

    ///情况3:在[l,r)范围中，由于两个子数组[l,mid)和[mid,r)分别有序，故可采用插入排序思想进行计算合并的逆序数
    int num = 0;
    for (int i = mid; i < r; i++) {
        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; j--) {
            arr[j] = arr[j - 1];
            num++;
        }
        arr[j] = e;
    }

    return num;
}

template<typename T>
int __mergec(T arr[], int l, int mid, int r) {
    //对于数组arr，其[l,mid)和[mid,r)内的子数组已有序
    //然后分情况讨论

    ///情况1:[l,r)范围内数组都有序
    if (arr[mid - 1] <= arr[mid])
        return 0;

    ///情况2:[l,mid)全部大于[mid,r)
    if (arr[l] > arr[r - 1]) {
        __inv(arr, l, mid, r);
        return (mid - l) * (r - mid);
    }

    ///情况3:在[l,r)范围中，通过寻找最小数组[l,min)，和最大数组[max,r)，缩小求解范围
    ///只需求得[min,max)中逆序数即可
    int min = l, max = r;
    //    while(arr[min] <= arr[mid])
    //        min++;
    //    while(arr[max-1] >= arr[mid-1])
    //        max--;

    int a_len = mid - min;
    int b_len = max - mid;
    T* a = SortTestHelper::copyIntArray(&arr[min], a_len);
    T* b = SortTestHelper::copyIntArray(&arr[mid], b_len);

    int num = 0, i = 0, j = 0;
    for (int k = min; k < max; k++) {
        if (i >= a_len) {
            ///这里不需要copy的原因是，当a结束时，b剩余的[j,b_len)的子数组与原arr[k,max)相同
            //copy(b+j,b+b_len,arr+k);
            break;
        }
        else if (j >= b_len)
        {
            copy(a + i, a + a_len, arr + k);
            break;
        }
        else if (a[i] > b[j]) {
            arr[k] = b[j];
            num += (a_len - i);
            j++;
        }
        else {
            arr[k] = a[i];
            i++;
        }
    }

    delete[] a;
    delete[] b;

    return num;
}

template<typename T>
int __inversions(T arr[], int l, int r, int type) {
    if (r - l <= 1)
        return 0;

    int mid = (l + r) / 2;
    int li = __inversions(arr, l, mid, type);
    int ri = __inversions(arr, mid, r, type);
    if (type == 0)
        return li + ri + __mergea(arr, l, mid, r);
    else if (type == 1)
        return li + ri + __mergeb(arr, l, mid, r);
    else if (type == 2)
        return li + ri + __mergec(arr, l, mid, r);
    else
        return 0;
}

//逆序数
template<typename T>
int inversions(T arr[], int n, int type)
{
    //防止在归并过程中，对原数组组成破坏
    T* temp = SortTestHelper::copyIntArray(arr, n);
    int result = __inversions(temp, 0, n, type);
    delete[] temp;
    return result;
}

void testInversions()
{
    int n = 1000000;
    //int* arr = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr = SortTestHelper::generateNearlyOrderedArray(n, 10000000);

    clock_t startTime = clock();
    int result = inversions(arr, n, 0);
    clock_t endTime = clock();
    cout << "算法1逆序数=" << result << ",时间：" << double(endTime - startTime) / CLK_TCK << " s" << endl;

    startTime = clock();
    result = inversions(arr, n, 1);
    endTime = clock();
    cout << "算法2逆序数=" << result << ",时间：" << double(endTime - startTime) / CLK_TCK << " s" << endl;

    startTime = clock();
    result = inversions(arr, n, 2);
    endTime = clock();
    cout << "算法3逆序数=" << result << ",时间：" << double(endTime - startTime) / CLK_TCK << " s" << endl;
}
#endif // INVERSIONS_H_INCLUDED
