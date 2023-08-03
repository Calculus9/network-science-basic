#include "iostream"
#include "vector"
#include "fstream"
#include "sstream"

#ifndef CPP_FUNCTION_H
#define CPP_FUNCTION_H

#endif // CPP_FUNCTION_H

//const int N = 10 + 5;

/**
 * 建图
 */


// 含权图
int** generateWeightedGraph(int n, bool directed = false, const std::string& path = "");

// 不含权
int** generateUnweightedGraph(int n, bool directed = false, const std::string& path = "");
/**
 * 求最短路
 */


// dij算法
int* dij(int n, int** e, int node);

//TODO:BFS

/**
* 网络模型
*/


//环状最近邻耦合网络
std::vector<std::vector<int>> generateRingNearestNeighborCoupledNet(int n, int k);
// 小世界网络
void generateWSSmallWorldNetwork(int n, int k, double p);


/**
 * 节点重要性与相似性
 */

int*calDegree(int** graph, int n);

// 度中心性
double* calDegreeCentrality(int* degree, int n);
//介数中心性
double* calBetweenessCentrality(int** graph, int n);
// 接近中心性
double* calClosenessCentrality(int** graph, int n);
/**
* 工具类
*/


// 转换vector为邻接矩阵
int** convertVectorToAdj(int n, std::vector<std::vector<int>> edge);
std::vector<std::vector<int>> convertAdjToVec(int n, int** graph,bool directed = false);
//将邻接矩阵生成csv文件
void write(int n, int** graph, const std::string& path);
//平均路径长度
double calCharacteristicPathLength(int n, int** graph);
//计算集聚系数
double averageClusterCoefficient(int n, int **graph);
double clusterCoefficient(int n, std::vector<std::vector<int>> v, int node);