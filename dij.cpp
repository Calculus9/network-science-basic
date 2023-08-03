#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
const int N = 9;
const int MAXN = 0x3f3f3f3f;

int path[N];
/**
 * Dijkstra算法，P95例子
 * @param n
 * @param graph
 */
bool vis[N];
void dij(int n, int e[N][N], int node)
{
    // 初始化：将所有路径都设置为无穷大,对角线设为0
    for (int i = 0; i < n; ++i)
    {
        path[i] = e[node][i] ? e[node][i] : MAXN;
        vis[i] = false;
    }
    path[node] = 0;
    vis[node] = 1;
    // S:当前已经确定最短路径的点
    // 开始找
    for (int i = 0; i < n; ++i)
    {
        int mn = MAXN, mn_i = 0;
        // 找到不在s中距离最近的点
        for (int j = 0; j < n; ++j)
        {
            if (i != j && !vis[j] && path[j] < mn)
            {
                mn_i = j;
                mn = path[j];
            }
        }
        // 把它加到s中去
        vis[mn_i] = 1; // 2  3 6 4 11 9
        // 根据新的节点来更新其他所有节点的距离
        for (int j = 0; j < n; ++j)
        {
            if (e[mn_i][j])
                path[j] = std::min(path[j], path[mn_i] + e[mn_i][j]);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        std::cout << path[i] << " ";
    }
}

int edge[N][N];
int main()
{
    // 创建流对象
    std::fstream fin;
    fin.open("edge.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "can't find " << std::endl;
        return 0;
    }
    // 建图
    std::string str;
    //    memset(edge, MAXN, sizeof edge);
    while (std::getline(fin, str))
    {
        std::stringstream ss;
        ss << str;
        int u, v, w;
        while (ss >> u >> v >> w)
        {
            edge[u][v] = w;
        }
    }
    fin.close();

    // 跑算法
    dij(9, edge, 0);
}