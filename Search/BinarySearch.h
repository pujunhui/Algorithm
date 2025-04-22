#pragma once

//二分搜索
template<typename T>
int binarySearch(T arr[], int n, T target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target)		//搜索目标在右半部分
            low = mid + 1;
        else if (arr[mid] > target)	//搜索目标在左半部分
            high = mid - 1;
        else 	                    //目标在当前位置
            return mid;
    }
    return -1; //未搜索到目标
}

//二分搜索（递归版）
template<typename T>
int __binarySearch2(T arr[], int low, int high, T target) {
    if (low > high) {
        return -1; //未搜索到目标
    }

    int mid = low + (high - low) / 2;
    if (arr[mid] < target) {
        return __binarySearch2(arr, mid + 1, high, target);
    }
    else if (arr[mid] > target) {
        return __binarySearch2(arr, low, mid - 1, target);
    }
    else {
        return mid;
    }
}

template<typename T>
int binarySearch2(T arr[], int n, T target) {
    return __binarySearch2(arr, 0, n - 1, target);
}
