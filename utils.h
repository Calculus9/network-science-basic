/**
 ******************************************************************************
 * @file           : utils.h
 * @author         : Jingyu.Huang
 * @brief          : 工具函数
 * @attention      : None
 * @date           : 2023/8/3
 ******************************************************************************
 */

#ifndef CPP_UTILS_H
#define CPP_UTILS_H

#endif // CPP_UTILS_H

#include "iostream"
#include "algorithm"
#include "vector"
#include "random"
#include "cstring"
#include "queue"
#include "map"
#include "unordered_map"
#include "unordered_set"


int** convertVectorToAdj(int n, std::vector<std::vector<int>> edge);

std::vector<std::vector<int>> convertAdjToVec(int n, int** graph);

void write(int n, int** graph, const std::string& path);

std::map<int,int> BFS(int node, std::vector<std::vector<int>> edge);

int* dij(int n, int** e, int node);

int dijstra(int n, std::vector<std::vector<int>> edge, int node, bool directed);