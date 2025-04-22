#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

//稀疏图-邻接表
//DFS:O(V+E)

template<typename Weight>
class SparseGraph
{
private:
    int n, m;				// 节点数和边数
    bool directed;			// 是否为有向图
    vector<vector<Edge<Weight>*>> g;  // 图的具体数据

public:
    SparseGraph(int n, bool directed) {
        assert(n >= 0);
        this->n = n;
        this->m = 0;    // 初始化没有任何边
        this->directed = directed;
        // g初始化为n个空的vector, 表示每一个g[i]都为空, 即没有任和边
        g = vector<vector<Edge<Weight> *> >(n, vector<Edge<Weight> *>());
    }

    ~SparseGraph() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < g[i].size(); j++)
                delete g[i][j];
    }

    //返回顶点个数Vertex
    int V() {
        return n;
    }

    //返回边的个数Edge
    int E() {
        return m;
    }

    void addEdge(int v, int w, Weight weight) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        // 注意, 由于在邻接表的情况, 查找是否有重边需要遍历整个链表
        // 我们的程序允许重边的出现

        g[v].push_back(new Edge<Weight>(v, w, weight));
        if (v != w && !directed)	//不是自环边且是无向图
            g[w].push_back(new Edge<Weight>(w, v, weight));

        m++;
    }

    //缺点:O(n)复杂度(未检测有无平行边)
    bool hasEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        for (int i = 0; i < g[v].size(); i++)
            if (g[v][i]->other(v) == w)
                return true;
        return false;
    }

    // 显示图的信息
    void show() {
        for (int i = 0; i < n; i++) {
            cout << "vertex " << i << ":\t";
            for (int j = 0; j < g[i].size(); j++)
                cout << "( to:" << g[i][j]->w() << ",wt:" << g[i][j]->wt() << ")\t";
            cout << endl;
        }
    }


    // 邻边迭代器, 传入一个图和一个顶点,
    // 迭代在这个图中和这个顶点向连的所有顶点
    // 算法时间复杂度O(E)
    class adjIterator {
    private:
        SparseGraph& G;		//图G的引用
        int v;
        int index;

    public:
        adjIterator(SparseGraph& graph, int v) :G(graph) {
            this->v = v;
            this->index = 0;
        }

        Edge<Weight>* begin() {
            index = 0;
            if (G.g[v].size())
                return G.g[v][index];
            // 若没有顶点和v相连接, 则返回-1
            return NULL;

        }

        Edge<Weight>* next() {
            index++;
            if (index < G.g[v].size())
                return G.g[v][index];
            return NULL;
        }

        bool end() {
            return index >= G.g[v].size();
        }
    };
};