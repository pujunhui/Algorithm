#include <iostream>

#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;

int main() {
	// 使用两种图的存储方式读取testG1.txt文件
	string filename = "testG1.txt";
	DenseGraph<double> g1 = DenseGraph<double>(8, false);
	ReadGraph<DenseGraph<double>,double> readGraph1(g1, filename);
	g1.show();
	cout << endl;

	SparseGraph<double> g2 = SparseGraph<double>(8, false);
	ReadGraph<SparseGraph<double>, double> readGraph2(g2, filename);
	g2.show();
	return 0;
}