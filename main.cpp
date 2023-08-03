#include "topologyProperties.h"

int main(){
    int n = 10;
    int** graph = generateUnweightedGraph(n, false, "kite.txt");
//    for (int i = 0; i < n; ++i)
//    {
//        for (int j = 0; j < n; ++j)
//        {
//            std::cout << graph[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    write(n, graph, "kite.csv");
//    int* degree = calDegree(graph, n);
//    double* degreeCentrality = calDegreeCentrality(degree, n);
    double* cc = calClosenessCentrality(graph, n);
    for (int i = 0; i < n; ++i)
    {
        std::cout << cc[i] << " ";
    }
    double res = averageClusterCoefficient(n, graph);
    std::cout << res << std::endl;
    //    int n = 8, k = 4;
//    int size = n + 5;
//    generateWSSmallWorldNetwork(n, k, 0.3);
    //    dij算法

//    int n = 9;
//    int** edge = generateWeightedGraph(n, false, "edge.txt");
//    int* dis = dij(n, edge, 0);
//    for (int i = 0; i < n; ++i)
//    {
//        std::cout << dis[i] << " ";
//    }

}