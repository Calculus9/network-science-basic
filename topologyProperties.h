/**
 ******************************************************************************
 * @file           : topologyProperties.h
 * @author         : Jingyu.Huang
 * @brief          : 拓扑性质
 * @attention      : None
 * @date           : 2023/8/3
 ******************************************************************************
 */
#include "function.h"
#include "iostream"
#include "algorithm"
#include "vector"
#include "random"
#include "cstring"
#include "queue"
#include "map"
#include "unordered_map"
#include "unordered_set"

#ifndef CPP_TOPOLOGYPROPERTIES_H
#define CPP_TOPOLOGYPROPERTIES_H

#endif // CPP_TOPOLOGYPROPERTIES_H

// 平均路径长度
double calCharacteristicPathLength(int n, int** graph);

//集聚系数
double averageClusterCoefficient(int n, int **graph);
double clusterCoefficient(int n, std::vector<std::vector<int>> v, int node);