#include "centrality.h"
#include "graph.h"
#include "network_model.h"
#include "topologyProperties.h"
#include "utils.h"
#include <iomanip>
#include "fstream"

int main(){
  double list[] = {0.0001, 0.00025, 0.0005, 0.00075, 0.001, 0.0025, 0.005, 0.0075, 0.01, 0.025, 0.05, 0.075,0.1000, 0.2500,0.5000, 0.7500, 1.0000};
  int n = 1000;
  int k = 10;
  std::vector<std::vector<int>> v = generateRingNearestNeighborCoupledNet(n,k);
//  write(n, convertVectorToAdj(n, v), "./ring.csv");
  double L = calPathLength(n, v);
  double C = averageClusterCoefficient(n, v);
  std::cout << L << " " << C << std::endl;
  int iter = 20;
  // 20
  std::fstream f;
  //追加写入,在原来基础上加了ios::app
  f.open("data.txt",std::ios::out| std::ios::app);
  //输入你想写入的内容
  for(auto p: list){
    // n * k
    std::vector<std::vector<int>> edge = generateRingNearestNeighborCoupledNet(n,k);
    double cur_l = 0.0, cur_c = 0.0;
    for (int j = 0; j < iter; ++j) {
      // n * k/2
      std::vector<std::vector<int>> net = generateWSSmallWorldNetwork(n, k, p, edge);
//      std::cout << "开始计算路径====" << std::endl;
      double l = calPathLength(n, net);
//      std::cout << "开始计算C====" << std::endl;
      double c = averageClusterCoefficient(n, net);
      cur_l += l;
      cur_c += c;
    }
//      double x = cur_c, y = cur_l;
    double x = cur_c / iter * 1.0, y = cur_l / iter * 1.0;
    f << p <<","<<y / L<< "," << x / C << std::endl;
    std::cout << p << std::setprecision(10) << " " << y / L << " " << x / C << std::endl;
  }

//    int n = 10;
//    int** graph = generateUnweightedGraph(n, false, "./data/kite.txt");
//    std::vector<std::vector<int>> edge = convertAdjToVec(n, graph);
//     构建规则图






//    generateWSSmallWorldNetwork(n, k, 0.3);
    //

//    std::vector<std::vector<int>> erRandomGraphNm= erRandomGraphNM(n,k);
//    for(const auto& x: erRandomGraphNm){
//      for(auto item:x){
//        std::cout << item << " ";
//      }
//      std::cout << std::endl;
//    }
//    int n = 10;
//    int** graph = generateUnweightedGraph(n, false, "./data/kite.txt");
//    write(n, graph, "./data/kite.csv");
//    calBetweenessCentrality(graph, n);
//    for (int i = 0; i < n; ++i) {
//
//    }
    //    double* degreeCentrality = calDegreeCentrality(degree, n);
//    for (int i = 0; i < n; ++i) {
//      std::cout << degreeCentrality[i] << " ";
//    }
//    double* cc = calClosenessCentrality(graph, n);
//    for (int i = 0; i < n; ++i)
//    {
//        std::cout << cc[i] << " ";
//    }
//    double res = averageClusterCoefficient(n, graph);
//    std::cout << res << std::endl;
    //    int n = 8, k = 4;
//    int size = n + 5;
//    generateWSSmallWorldNetwork(n, k, 0.3);
    //    dij�㷨

//    int n = 9;
//    int** edge = generateWeightedGraph(n, false, "edge.txt");
//    int* dis = dij(n, edge, 0);
//    for (int i = 0; i < n; ++i)
//    {
//        std::cout << dis[i] << " ";
//    }

}