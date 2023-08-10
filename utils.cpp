/**
 ******************************************************************************
 * @file           : utils.cpp
 * @author         : Jingyu.Huang
 * @brief          : 工具函数
 * @attention      : None
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
#include "fstream"

/**
 * 转换邻接矩阵为邻接表
 * @param n 节点数目
 * @param graph 邻接矩阵graph
 * @param directed 是否是有向图
 * @return 图的邻接表
 */
std::vector<std::vector<int>> convertAdjToVec(int n, int** graph){
    std::vector<std::vector<int>> edge(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (graph[i][j]){
                edge[i].push_back(j);
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
    int size = n;
    int** e = new int* [size];
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


/**
 * 向csv文件写入邻接矩阵
 * @param n 节点数目
 * @param graph 邻接矩阵
 * @param path 文件路径
 */
void write(int n, int** graph, const std::string& path){
    // 向csv文档中写入数据
    std::ofstream dataFile;
    dataFile.open(path, std::ios::out | std::ios::trunc);
    dataFile << ",";
    for (int i = 0; i < n; ++i)
    {
        dataFile << i << ",";
    }
    dataFile << std::endl;
    for (int i = 0; i < n; i = i + 1)
    {
        dataFile << i << ",";
        for (int j = 0; j < n; j = j + 1)
        {
            dataFile << graph[i][j] << ",";          // 写入数据
        }
        dataFile <<  std::endl;                       // 换行
    }
    std::cout << "写入文件结束" << std::endl;
    dataFile.close();       // 关闭文档
}

/**
 * BFS求最短路
 * @param node
 * @param edge
 * @return node到其他节点的距离
 */
std::map<int,int> BFS(int node, std::vector<std::vector<int>> edge){
    std::queue<int>q;//用于bfs
    std::unordered_set<int>vis;//记录是否访问过当前节点
    std::map<int,int> mp;//用于node到当前节点的距离

    q.push(node);
    vis.insert(node);
    mp[node] = 0;
    while (!q.empty()){
        int top = q.front(); q.pop();
        // 遍历其所有邻居节点
        for (auto x: edge[top])
        {
            if (vis.find(x) == vis.end()){
                vis.insert(x);
                q.push(x);
                mp[x] = mp[top] + 1;
            }
        }
    }
    return mp;
}

int dijstra(int n, std::vector<std::vector<int>> edge, int node, bool directed){
    const int MAXN = 100010, size = n;
    bool vis[size];
    memset(vis, false, sizeof vis);
    std::vector<int> dis(n + 10, MAXN);
    for(auto x: edge[node]){
        dis[x] = 1;
    }

    // 初始化：将所有路径都设置为无穷大,对角线设为0
//    for (int i = 0; i < n; ++i)
//    {
//        dis[i] = edge[node][i] ? edge[node][i] : MAXN;
//        vis[i] = false;
//    }
    dis[node] = 0;
    vis[node] = true;

    // S:当前已经确定最短路径的点
    // 开始找
    for (int i = 0; i < n; ++i)
    {
        int mn = MAXN, mn_i = 0;
        // 找到不在s中距离最近的点
        for (int j = 0; j < n; ++j)
        {
            if (i != j && !vis[j] && dis[j] < mn)
            {
                mn_i = j;
                mn = dis[j];
            }
        }
        // 把它加到s中去
        vis[mn_i] = true; // 2  3 6 4 11 9
        // 根据新的节点来更新其他所有节点的距离
        for (int j = 0; j < n; ++j)
        {
            if (std::find(edge[mn_i].begin(), edge[mn_i].end(), j) != edge[mn_i].end())
                dis[j] = std::min(dis[j], dis[mn_i] + 1);
        }
    }
    int res = 0;
    for(auto x: dis){
        res += x;
    }
    return res;
}

/**
 * dij最短路径算法
 * @param n 节点数
 * @param e 邻接矩阵
 * @param node 源节点
 * @return 长度路径
 */
int* dij(int n, int** e, int node)
{
    const int MAXN = 0x3f3f3f3f, size = n;
    bool vis[size];
    static int* dis = new int[n];
    // 初始化：将所有路径都设置为无穷大,对角线设为0
    for (int i = 0; i < n; ++i)
    {
        dis[i] = e[node][i] ? e[node][i] : MAXN;
        vis[i] = false;
    }
    dis[node] = 0;
    vis[node] = true;
    // S:当前已经确定最短路径的点
    // 开始找
    for (int i = 0; i < n; ++i)
    {
        int mn = MAXN, mn_i = 0;
        // 找到不在s中距离最近的点
        for (int j = 0; j < n; ++j)
        {
            if (i != j && !vis[j] && dis[j] < mn)
            {
                mn_i = j;
                mn = dis[j];
            }
        }
        // 把它加到s中去
        vis[mn_i] = true; // 2  3 6 4 11 9
        // 根据新的节点来更新其他所有节点的距离
        for (int j = 0; j < n; ++j)
        {
            if (e[mn_i][j])
                dis[j] = std::min(dis[j], dis[mn_i] + e[mn_i][j]);
        }
    }
    return dis;
}
