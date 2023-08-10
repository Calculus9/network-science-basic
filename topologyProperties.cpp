/**
 ******************************************************************************
 * @file           : topologyProperties.cpp
 * @author         : Jingyu.Huang
 * @brief          : 用于计算网络的拓扑性质。
 * @attention      : None
 ******************************************************************************
 */
#include "utils.h"
#include "iostream"
#include "algorithm"
#include "vector"
#include "cstring"
#include "queue"
/**
 * 计算度值
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return 度值数组
 */
int* calDegree(int** graph, int n){
  int* degree = new int[n + 5];
  for (int i = 0; i < n; ++i)
  {
    degree[i] = 0;
    for (int j = 0; j < n; ++j)
    {
      degree[i] += graph[i][j] == 1;
    }
  }
  return degree;
}

/**
 * ===========================================================================
 * 集聚系数
 * ===========================================================================
 */

/**
 * 计算节点node的集聚系数
 * @param n 图的节点数目
 * @param v 邻接表
 * @param node 节点node
 * @return 节点node的集聚系数值
 */
double clusterCoefficient(std::vector<std::vector<int>> v, int node)
{
    double res = 0.0;
    int size = v[node].size();
    for(auto x: v[node]){
        for(auto y: v[node]){
            if (x != y && std::find(v[x].begin(), v[x].end(), y) != v[x].end() &&
                std::find(v[y].begin(), v[y].end(), x) != v[y].end()
            ){
                res += 1.0;
            }
        }
    }

    return res * 1.0 ? res / ((size - 1) * size) : 0;
}

/**
 * 平均集聚系数
 * @param n 图的节点数目
 * @param graph 邻接矩阵
 * @return 平均集聚系数
 */
double averageClusterCoefficient(int n, std::vector<std::vector<int>> v){
    //初始化
    double res = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double c_i = clusterCoefficient(v, i);
        res += 1.0 * c_i;
    }
    return res * 1.0 / n;
}

/**
 * ===========================================================================
 * 平均路径长度
 * ===========================================================================
 */

double calPathLength(int n, std::vector<std::vector<int>> edge){
//    std::cout << "111" << std::endl;
    std::queue<int> q{};
    std::map<int,int>mp{};
    int result = 0;
    for (int i = 0; i < n; ++i) {
        std::map<int,int> dis = BFS(i, edge);
        for (int j = i + 1; j < n; ++j) {
          result += dis[j];
        }
    }
    return result * 2.0 / (n * (n - 1));
}
//TODO:写法太复杂，待优化
double calCharacteristicPathLength(int n, int** graph){
    int path[n + 5][n + 5];
    std::queue<int> q;
    bool vis[n + 5];
    memset(path, 99 , sizeof path);
    int step = 1;
    // 对每个节点遍历找到其对应的最小值
    for (int i = 0; i < n; ++i) {
        q.push(i);
        memset(vis, false, sizeof vis);
        vis[i] = true;
        std::queue<int> curLevel;
        while (!q.empty()){
            while (!q.empty()) {
                curLevel.push(q.front());
                q.pop();
            }
            while (!curLevel.empty()){
                int node = curLevel.front();
                for (int j = 0; j < n; ++j) {
                    if(j == node){
                        path[j][j] = 0;
                        continue;
                    }
                    if(graph[node][j]){
                        path[node][j] = path[j][node] = 1;
                        // 取最小值，后面再次找到时会修改这个地方
                        path[i][j] = path[j][i] = std::min(step, path[j][i]);
                        if(!vis[j]) {
                            vis[j] = true;
                            q.push(j);
                        }
                    }
                }
                curLevel.pop();
            }
            step ++;
        }
        step = 1;
    }
    int res = 0.0;
    for(int i = 0;i < n; i+= 1){
        for(int j = 0; j < n; j += 1) {
            res += path[i][j];
        }
    }
    return 1.0 * res / (n * (n-1));
}
