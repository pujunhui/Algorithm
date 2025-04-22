#pragma once

#include<assert.h>

namespace UF4 {
    class UnionFind {
    private:
        int* parent; // parent[i]表示第i个元素所指向的父节点
        int* rank;//rank[i]表示以i为根的集合所表示的树的层数
        int count;// 数据个数

    public:
        UnionFind(int count) {
            parent = new int[count];
            rank = new int[count];
            this->count = count;
            // 初始化, 每一个parent[i]指向自己, 表示每一个元素自己自成一个集合
            for (int i = 0; i < count; i++) {
                parent[i] = i;
                rank[i] = 1;
            }
        }

        ~UnionFind() {
            delete[] parent;
            delete[] rank;
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

            if (pRoot == qRoot)
                return;

            if (rank[pRoot] < rank[qRoot]) {
                parent[pRoot] = qRoot;
            }
            else if (rank[pRoot] > rank[qRoot]) {
                parent[qRoot] = pRoot;
            }
            else {//rank[pRoot] = rank[qRoot]
                parent[pRoot] = qRoot;
                rank[qRoot]++;
            }
        }
    };
}