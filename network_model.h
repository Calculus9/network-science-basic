#include <vector>
#ifndef CPP_NETWORK_MODEL_H
#define CPP_NETWORK_MODEL_H

#endif // CPP_NETWORK_MODEL_H
//er随机图G(m,n)
std::vector<std::vector<int>> erRandomGraphNM(int n, int k);

// 环状最近邻耦合网络
std::vector<std::vector<int>> generateRingNearestNeighborCoupledNet(int n, int k);
// 小世界网络
std::vector<std::vector<int>> generateWSSmallWorldNetwork(int n, int k, double p, std::vector<std::vector<int>> edge);

std::vector<std::vector<int>> generateSmallWorldNetwork(const std::vector<std::vector<int>>& initialEdge, double p);