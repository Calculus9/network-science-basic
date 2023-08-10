

#include <map>
#include <queue>
#include <vector>
#include "utils.h"

/**
 * 计算度中心性
 * @param degree 度值数组
 * @param n 节点数目
 * @return 返回各个节点的度中心性列表
 */
double* calDegreeCentrality(const int* degree, int n){
  auto* degreeCentrality = new double[n + 5];
  for (int i = 0; i < n; ++i)
  {
    degreeCentrality[i] = degree[i] * 1.0 / (n - 1);
  }
  return degreeCentrality;
}

// 计算节点对之间的最短路径数量
std::vector<int> calShortestPathCnts(int n, int** graph, int start){
  std::vector<std::vector<int>> edge = convertAdjToVec(n, graph);
  // BFS计算其最短路径
  std::queue<int> q;//进行bfs
  std::vector<int> dis(edge.size());//到start节点的最短路径
  std::vector<int> paths(edge.size(), 0);// 到start节点的最短路径数目
  q.push(start);
  dis[start] = 0;
  paths[start] = 1;
  while (!q.empty()){
    int top = q.front(); q.pop();
    for (auto item : edge[top]) {
      if (start != item && dis[item] == 0){
        q.push(item);
        dis[item] = dis[top] + 1;
      }
      if(dis[item] == dis[top] + 1){//当前节点是最短节点
        paths[item] += paths[top];
      }
    }
  }
  return paths;
}

/**
 * 计算介数中心性
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return
 */
void* calBetweenessCentrality(int** graph, int n){
  std::vector<int> shortestPathCnts;
  for (int i = 0; i < n; ++i) {
    shortestPathCnts = calShortestPathCnts(n, graph, i);
    for (auto item: shortestPathCnts) {
      std::cout << item << " ";
    }
  }
}
/**
 * 计算i节点的所有路径。
 * @return i节点的路径和
 */
double calD_i(int n, const std::vector<std::vector<int>>& edge){
  double cc = 0.0, res = 0.0;
  auto* d_i = new double [n];
  for (int i = 0; i < n; ++i)
  {
    // 求得节点node到其他节点的距离为BFS
    std::map<int, int>mp = BFS(i, edge);
    cc = 0.0;
    for(auto x: mp){
      cc += x.second;
    }
    d_i[i] = (n - 1) / cc;
    res += d_i[i];
    std::cout << "节点" << i << "的接近数是" << d_i[i] << std::endl;
  }
  return res / n;
}
/**
 * 计算接近中心性
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return
 */
double* calClosenessCentrality(int** graph, int n){
  std::vector<std::vector<int>> edge = convertAdjToVec(n, graph);
  std::cout << calD_i(n, edge) << "---平均";
}
