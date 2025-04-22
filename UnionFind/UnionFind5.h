#pragma once

#include<assert.h>

namespace UF5 {
    class UnionFind {
    private:
        // rank[i]表示以i为根的集合所表示的树的层数
        // 事实上，这正是我们将这个变量叫做rank而不是叫诸如depth或者height的原因。
        // 因为这个rank只是我们做的一个标志当前节点排名的一个数字，当我们引入了路径压缩以后，
        // 维护这个深度的真实值相对困难一些，而且实践告诉我们，我们其实不需要真正维持这个值是真实的深度值，
        // 我们依然可以以这个rank值作为后续union过程的参考。因为根据我们的路径压缩的过程，
        // rank高的节点虽然被抬了上来，但是整体上，我们的并查集从任意一个叶子节点出发向根节点前进，
        // 依然是一个rank逐渐增高的过程。也就是说，这个rank值在经过路径压缩以后，虽然不是真正的深度值，
        // 但仍然可以胜任，作为union时的参考。
        // 关于这个问题，可以参考问答区：http://coding.imooc.com/learn/questiondetail/7287.html
        int* rank;
        int* parent; // parent[i]表示第i个元素所指向的父节点
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
            {
                parent[p] = parent[parent[p]];
                p = parent[p];
            }

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