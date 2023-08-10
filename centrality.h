
#include "iostream"
#include "map"
#ifndef CPP_CENTRALITY_H
#define CPP_CENTRALITY_H

#endif // CPP_CENTRALITY_H

//度中心性
double* calDegreeCentrality(const int* degree, int n);
// 接近中心性
double* calClosenessCentrality(int** graph, int n);
// 计算最短路径数量
std::map<int, int>calShortestPathCnts(int n, int** graph, int s);
// 介数中心性
double* calBetweenessCentrality(int** graph, int n);