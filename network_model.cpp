
/**
* 网络模型
 */
#include <vector>
#include "utils.h"

/**
 * 生成ER随即图G(N,M)
 * @param n 节点数
 * @param k 待添加的边数
 * @return 邻接表
 */
std::vector<std::vector<int>> erRandomGraphNM(int n, int k){
  std::vector<std::vector<int>> random(n, std::vector<int>(n, 0));
  for (int i = 0; i < k; ++i) {
    // 随机连边
    std::random_device rd;// 获取随机设备的种子
    std::mt19937 gen(rd()); // 使用随机种子初始化随机数引擎
    std::uniform_int_distribution<int> m(0, n - 1);// 随机生成一个整数
    int x = m(gen), y = m(gen);
    while (x == y or random[x][y] == 1){
      x = m(gen), y = m(gen);
    }
    random[x][y] = 1;
    random[y][x] = 1;
  }
  return random;
}

/**
 * 生成ER随机图G(N,p)
 * @param n
 * @param p
 * @return
 */
std::vector<std::vector<int>> erRandomGraphNp(int n, int p){
  std::vector<std::vector<int>> random(n, std::vector<int>(n, 0));
  // 增长
  int m0 = 3, m = 2;

  // 优先连接

}

/**
 * 环状最近邻耦合网络
 * @param n
 * @param k
 * @return
 */
std::vector<std::vector<int>> generateRingNearestNeighborCoupledNet(int n, int k){
  std::vector<std::vector<int>> edge(n + 10);
  for (int i = 0; i < n; ++i)
  {
    for (int j = i + 1; j <= (i + k / 2); ++j)
    {
      int u = i, v = j % n;
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
  }
  return edge;
}

// WS小世界网络
std::vector<std::vector<int>> generateWSSmallWorldNetwork(int n, int k, double p, std::vector<std::vector<int>> edge)
{
  // 随机化重连
  std::random_device rd;// 获取随机设备的种子
  std::mt19937 gen(rd()); // 使用随机种子初始化随机数引擎
  std::uniform_real_distribution<double> disProbability(0.00001, 1.00000);// 随机生产0~1之间的数
  std::uniform_int_distribution<int> disInteger(0, n - 1);// 随机生成一个整数
  for (int i = 0; i < n; ++i)
  {
//    for (int j = i + 1; j <= (i + k / 2); ++j)
    for (int j = i + 1; j <= (i + k / 2); ++j){
      int jj = j % n;
      double x = disProbability(gen);
      if (x < p){
        //随机重连
        int newNeighbor = disInteger(gen);
        // 不能有重边和自环
        if (std::find(edge[i].begin(), edge[i].end(), newNeighbor) == edge[i].end() && i != newNeighbor){
          /**
            * 更新操作：将原有的i，j换为i neighbor
           */
          // j -> i 取消
          edge[jj].erase(std::find(edge[jj].begin(), edge[jj].end(), i));
          edge[i].erase(std::find(edge[i].begin(), edge[i].end(), jj));
          // newNeighbor - i
          edge[newNeighbor].push_back(i);
          edge[i].push_back(newNeighbor);
        }
      }
    }
  }
//  int** swGraph = convertVectorToAdj(n, edge);
//  write(n, swGraph, "WSSmallWorld.csv");
  return edge;
}

std::vector<std::vector<int>> generateSmallWorldNetwork(const std::vector<std::vector<int>>& initialEdge, double p) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> disProbability(0.0, 1.0);

  std::vector<std::vector<int>> edge = initialEdge;
  int n = edge.size();

  for (int i = 0; i < n; ++i) {
    for (int j : edge[i]) {
      double x = disProbability(gen);
      if (x < p) {
        int newNeighbor = i;
        while (newNeighbor == i || std::find(edge[i].begin(), edge[i].end(), newNeighbor) != edge[i].end()) {
          newNeighbor = gen() % n;
        }
        edge[j].erase(std::remove(edge[j].begin(), edge[j].end(), i), edge[j].end());
        edge[i].erase(std::remove(edge[i].begin(), edge[i].end(), j), edge[i].end());
        edge[newNeighbor].push_back(i);
        edge[i].push_back(newNeighbor);
      }
    }
  }

  return edge;
}