#pragma once

#include<assert.h>

namespace UF1 {
    class UnionFind {
    private:
        int* id; // 我们的第一版Union-Find本质就是一个数组
        int count;// 数据个数

    public:
        UnionFind(int n) {
            id = new int[n];
            count = n;
            // 初始化, 每一个id[i]指向自己, 没有合并的元素
            for (int i = 0; i < n; i++) {
                id[i] = i;
            }
        }

        ~UnionFind() {
            delete[] id;
        }

        // 查找过程, 查找元素p所对应的集合编号
        int find(int p) {
            assert(p >= 0 && p < count);
            return id[p];
        }

        bool isConnected(int p, int q) {
            return find(p) == find(q);
        }

        void unionElements(int p, int q) {
            int pID = find(p);
            int qID = find(q);

            if (pID == qID)
                return;

            //遍历一遍，将pID的元素放入pID中，实质是将所有pID改成qID
            for (int i = 0; i < count; i++) {
                if (id[i] == pID) {
                    id[i] = qID;
                }
            }
        }
    };
}