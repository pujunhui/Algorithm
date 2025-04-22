#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

//稠密图-邻接矩阵
//DFS:O(V^2)
template <typename Weight>
class DenseGraph
{
private:
	int n, m;       // 节点数和边数
	bool directed;  // 是否为有向图
	vector<vector<Edge<Weight>*>> g; // 图的具体数据

public:
	DenseGraph(int n, bool directed) {
		assert(n >= 0);
		this->n = n;
		this->m = 0;    // 初始化没有任何边
		this->directed = directed;
		// g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
		g = vector<vector<Edge<Weight> *>>(n, vector<Edge<Weight> *>(n, NULL));
	}

	~DenseGraph() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (g[i][j] != NULL)
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

	// 向图中添加一个边
	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		if (hasEdge(v, w)) {	//若不判断，重复添加边将会造成m不正确
			delete g[v][w];
			if (v != w && !directed)
				delete g[w][v];
			m--;
		}

		g[v][w] = new Edge<Weight>(v, w, weight);
		if (v != w && !directed)
			g[w][v] = new Edge<Weight>(w, v, weight);;

		m++;
	}

	// 验证图中是否有从v到w的边
	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w] != NULL;
	}

	// 显示图的信息
	void show() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				if (g[i][j])
					cout << g[i][j]->wt() << "\t";
				else
					cout << "NULL\t";
			cout << endl;
		}
	}


	// 邻边迭代器, 传入一个图和一个顶点,
	// 迭代在这个图中和这个顶点向连的所有顶点
	// 时间复杂度：O(V^2)
	class adjIterator {
	private:
		DenseGraph &G;
		int v;
		int index;

	public:
		adjIterator(DenseGraph &graph, int v) :G(graph) {
			this->v = v;
			this->index = -1;
		}

		Edge<Weight>* begin() {
			index = -1;
			return next();
		}

		Edge<Weight>* next() {
			// 从当前index开始向后搜索, 直到找到一个g[v][index]为true
			for (index++; index < G.V(); index++)
				if (G.g[v][index])
					return G.g[v][index];
			// 若没有顶点和v相连接, 则返回-1
			return NULL;
		}

		bool end() {
			return index >= G.V();
		}
	};
};
