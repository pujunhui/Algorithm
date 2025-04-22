#include<iostream>
#include<ctime>

#include"UnionFind1.h"
#include"UnionFind2.h"
#include"UnionFind3.h"
#include"UnionFind4.h"
#include"UnionFind5.h"
#include"UnionFind6.h"

template <typename UnionFind>
double testUnionFind(int n) {
    srand(time(NULL));
    UnionFind uf = UnionFind(n);

    time_t startTime = clock();

    for (int i = 0; i < n; i++) {
        int a = rand() % n;
        int b = rand() % n;
        uf.unionElements(a, b);
    }

    for (int i = 0; i < n; i++) {
        int a = rand() % n;
        int b = rand() % n;
        uf.isConnected(a, b);
    }

    time_t endTime = clock();

    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
    int n = 100000;

    cout << "UF1 " << testUnionFind<UF1::UnionFind>(n) << " s" << endl;
    cout << "UF2 " << testUnionFind<UF2::UnionFind>(n) << " s" << endl;
    cout << "UF3 " << testUnionFind<UF3::UnionFind>(n) << " s" << endl;
    cout << "UF4 " << testUnionFind<UF4::UnionFind>(n) << " s" << endl;
    cout << "UF5 " << testUnionFind<UF5::UnionFind>(n) << " s" << endl;
    cout << "UF6 " << testUnionFind<UF6::UnionFind>(n) << " s" << endl;

    return 0;
}
