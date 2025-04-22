#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

//利用广度优先算法求无全图最短途径
template<typename Graph>
class ShortestPath {
private:
    Graph& G;       // 图的引用
    int s;          // 起始点
    bool* visited;  // 记录dfs的过程中节点是否被访问
    int* from;      // 记录路径, from[i]表示查找的路径上i的上一个节点
    int* ord;       // 记录路径中节点的次序。ord[i]表示i节点在路径中的次序。

public:
    ShortestPath(Graph& graph, int s) :G(graph) {
        //算法初始化
        assert(s >= 0 && s < G.V());

        visited = new bool[G.V()];
        from = new int[G.V()];
        ord = new int[G.V()];
        for (int i = 0; i < G.V(); i++) {
            visited[i] = false;
            from[i] = -1;
        }
        this->s = s;

        // 无向图最短路径算法, 从s开始广度优先遍历整张图
        queue<int> q;

        q.push(s);
        visited[s] = true;
        ord[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            typename Graph::adjIterator adj(G, v);
            for (int i = adj.begin(); !adj.end(); i = adj.next())
                if (!visited[i]) {
                    q.push(i);
                    visited[i] = true;
                    from[i] = v;
                    ord[i] = ord[v] + 1;
                }
        }
    }

    ~ShortestPath() {
        delete[] visited;
        delete[] from;
        delete[] ord;
    }

    // 查询从s点到w点是否有路径
    bool hasPath(int w) {
        assert(w >= 0 && w < G.V());
        return visited[w];
    }

    // 查询从s点到w点的路径, 存放在vec中
    void path(int w, vector<int>& vec) {

        assert(w >= 0 && w < G.V());

        stack<int> s;

        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        int p = w;
        while (p != -1) {
            s.push(p);
            p = from[p];
        }

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        vec.clear();
        while (!s.empty()) {
            vec.push_back(s.top());
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void showPath(int w) {

        assert(hasPath(w));

        vector<int> vec;
        path(w, vec);
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i == vec.size() - 1)
                cout << endl;
            else
                cout << " -> ";
        }
    }

    int length(int w) {
        assert(w >= 0 && w < G.V());
        return ord[w];
    }
};