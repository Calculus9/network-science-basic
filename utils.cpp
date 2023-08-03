/**
 ******************************************************************************
 * @file           : utils.cpp
 * @author         : Jingyu.Huang
 * @brief          : 工具函数
 * @attention      : None
 * @date           : 2023/8/3
 ******************************************************************************
 */
#include "iostream"
#include "algorithm"
#include "vector"
#include "random"
#include "cstring"
#include "queue"
#include "map"
#include "unordered_map"
#include "unordered_set"

/**
 * 转换邻接矩阵为邻接表
 * @param n 节点数目
 * @param graph 邻接矩阵graph
 * @param directed 是否是有向图
 * @return 图的邻接表
 */
std::vector<std::vector<int>> convertAdjToVec(int n, int** graph,bool directed){
    std::vector<std::vector<int>> edge(n + 5);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (graph[i][j]){
                edge[i].push_back(j);
                //                if (!directed) edge[j].push_back(i);
            }
        }
    }
    return edge;
}

/**
 * 邻接表为邻接矩阵
 * @param n 节点数目
 * @param edge 邻接表
 * @param e 邻接矩阵
 * @return e
 */
int** convertVectorToAdj(int n, std::vector<std::vector<int>> edge){
    int size = n  + 5;
    int** e = new int * [size];
    for (int i = 0; i < n; ++i) e[i] = new int[size];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (std::find(edge[i].begin(), edge[i].end(), j) != edge[i].end())
            {
                e[i][j] = 1;
            }
            else
            {
                e[i][j] = 0;
            }
        }
    }
    return e;
}