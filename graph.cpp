
#include "iostream"
#include "algorithm"
#include "random"
#include "fstream"
#include "sstream"

/**
 * 生成含权图
 * @param n 节点数目
 * @param directed 是否有向
 * @param path 读取文件路径
 * @return 邻接矩阵
 */
int** generateWeightedGraph(int n, bool directed, const std::string& path){
  int size = n + 5;
  int** edge = new int*[size]; //先创建n个一维数组。
  for (int i = 0; i < n; ++i)//再在这n个一维数组中开辟空间。
    edge[i] = new int[size];

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      edge[i][j] = 0;
    }
  }

  // 创建流对象
  std::fstream fin;
  fin.open(path, std::ios::in);
  if (!fin.is_open())
  {
    std::cout << "can't find " << std::endl;
  }

  // 建图
  std::string str;
  //    memset(edge, MAXN, sizeof edge);
  while (std::getline(fin, str))
  {
    std::stringstream ss;
    ss << str;
    int u, v, w = 1;
    while (ss >> u >> v >> w)
    {
      edge[u][v] = w;
      if (!directed){
        edge[v][u] = w;
      }
    }
  }
  fin.close();
  return edge;
}


int** generateUnweightedGraph(int n, bool directed, const std::string& path){
  int size = n + 5;
  int** edge = new int*[size]; //先创建n个一维数组。
  for (int i = 0; i < n; ++i)//再在这n个一维数组中开辟空间。
    edge[i] = new int[size];

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      edge[i][j] = 0;
    }
  }

  // 创建流对象
  std::fstream fin;
  fin.open(path, std::ios::in);
  if (!fin.is_open())
  {
    std::cout << "can't find " << std::endl;
  }

  // 建图
  std::string str;
  //    memset(edge, MAXN, sizeof edge);
  while (std::getline(fin, str))
  {
    std::stringstream ss;
    ss << str;
    int u, v;
    while (ss >> u >> v)
    {
      edge[u][v] = 1;
      if (!directed){
        edge[v][u] = 1;
      }
    }
  }
  fin.close();
  return edge;
}
