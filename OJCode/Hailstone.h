#ifndef HAILSTONE_H_INCLUDED
#define HAILSTONE_H_INCLUDED

#include<iostream>

using namespace std;

int hailstone(int arr[], int len, int n) {
    int resN = 1;
    arr[0] = n;
    for (int i = 1; i < len; i++) {
        int prev = arr[i - 1];
        if (prev == 1)
            break;
        else if (prev % 2 == 0)
            arr[i] = prev / 2;
        else
            arr[i] = prev * 3 + 1;
        resN++;
    }
    return resN;
}

void testHailstone() {
    int len = 100, n, res;
    cin >> n;
    int* arr = new int[len];
    res = hailstone(arr, len, n);
    for (int i = 0; i < res; i++)
        cout << arr[i] << " ";
    delete[] arr;
}
#endif // HAILSTONE_H_INCLUDED
