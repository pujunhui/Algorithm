#pragma once
/**
* 插值查找
* 类似于二分查找算法，但查找位置是根据比例确定的
* 适用分布均匀的有序数据集中
*/

template<typename T>
int insertionSearch(T arr[], int n, T target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        //假设均匀分布，计算比列
        float factor = (float)(target - arr[low]) / (arr[high] - arr[low]);
        //根据比列，求得大概位置
        int pos = low + (int)((high - low) * factor);
        if (arr[pos] < target) {
            low = pos + 1;
        }
        else if (arr[pos] > target) {
            high = pos - 1;
        }
        else {
            return pos;
        }
    }
    return -1;
}
