#pragma once

#include<assert.h>

namespace UF2 {
    class UnionFind {
    private:
        // 我们的第二版Union-Find, 使用一个数组构建一棵指向父节点的树
        int* parent;// parent[i]表示第i个元素所指向的父节点
        int count; // 数据个数

    public:
        UnionFind(int count) {
            parent = new int[count];
            this->count = count;
            // 初始化, 每一个parent[i]指向自己, 表示每一个元素自己自成一个集合
            for (int i = 0; i < count; i++) {
                parent[i] = i;
            }
        }

        ~UnionFind() {
            delete[] parent;
        }

        int find(int p) {
            assert(p >= 0 && p < count);
            // 不断去查询自己的父亲节点, 直到到达根节点
            // 根节点的特点: parent[p] == p
            while (p != parent[p])
                p = parent[p];
            return p;
        }

        bool isConnected(int p, int q) {
            return find(p) == find(q);
        }

        void unionElements(int p, int q) {
            int pRoot = find(p);
            int qRoot = find(q);

            if (pRoot == qRoot) {
                return;
            }

            parent[pRoot] = qRoot;
        }
    };
}