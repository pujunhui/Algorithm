#include<iostream>
#include"OrderSearch.h"
#include"BinarySearch.h"
#include"InsertionSearch.h"

using namespace std;

template<typename T>
void testSearch(string searchName, int(*search)(T[], int, T), T arr[], int n, T target)
{
    clock_t startTime = clock();
    int i = search(arr, n, target);
    clock_t endTime = clock();

    cout << searchName << " : " << double(endTime - startTime) / CLK_TCK << " s, index=" << i << endl;
}

int main(int argc, char* argv[]) {
    int arr[100000];
    for (int i = 0; i < 100000; i++) {
        arr[i] = i + 3;
    }

    int n;
    cin >> n;

    testSearch("Order Search", orderSearch, arr, 100000, n);
    testSearch("Insertion Search", insertionSearch, arr, 100000, n);
    testSearch("Binary Search", binarySearch2, arr, 100000, n);

    return 0;
}