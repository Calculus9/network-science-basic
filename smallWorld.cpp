//
// Created by 14412 on 2023/7/30.
//
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
const int N = 500;
int e[N + 4][N + 4];
std::vector<int> edge[N + 4];
std::vector<int>::iterator it;

double calCharacteristicPathLength(int n, int graph[N+4][N+4]){
    int path[N][N];
    std::queue<int>q;
    bool vis[N];
    int step = 1;
    memset(path, 99, sizeof path);
    // 对每个节点遍历找到其对应的最小值
    for (int i = 0; i < n; ++i) {
        q.push(i);
        memset(vis, false, sizeof vis);
        vis[i] = true;
        std::queue<int> curLevel;
        while (!q.empty()){
            while (!q.empty()) {
                curLevel.push(q.front());
                q.pop();
            }
            while (!curLevel.empty()){
                int node = curLevel.front();
                for (int j = 0; j < n; ++j) {
                    if(j == node){
                        path[j][j] = 0;
                        continue;
                    }
                    if(graph[node][j]){
                        path[node][j] = path[j][node] = 1;
                        // 取最小值，后面再次找到时会修改这个地方
                        path[i][j] = path[j][i] = std::min(step, path[j][i]);
                        if(!vis[j]) {
                            vis[j] = true;
                            q.push(j);
                        }
                    }
                }
                curLevel.pop();
            }
            step ++;
        }
        step = 1;
    }
    int res = 0.0;
    for(int i = 0;i < n; i+= 1){
        for(int j = 0; j < n; j += 1) {
            res += path[i][j];
        }
    }
    return 1.0 * res / (n * (n-1));
}
double cluster_coefficient(int n, int graph[N+4][N+4]){
    //初始化
    double res = 0.0, ans = 0.0;
    std::vector<std::vector<int>> v(N);
    std::vector<std::vector<int>>::iterator iter;

    for (int i = 0; i < n; i+= 1)
        for(int j = 0; j < n; j+= 1)
            if (graph[i][j]) v[i].push_back(j);
    for (iter = v.begin(); iter != v.end(); ++iter){
        std::vector<int> row = *iter;
        if(row.size() < 2){
            res = 0.0;
            continue;
        }
        for (int i = 0; i < row.size(); ++i) {
            for(int j = i + 1; j < row.size(); ++j){
                int x = row[i], y = row[j];
                if (graph[x][y]){
                    res += 1.0;
                }
            }
        }
        int len = row.size();
        double c_i = 2.0 * res / (len * (len - 1));
        //        std::cout << 2.0 * res / (row.size() * (row.size() - 1)) << std::endl;
        res = 0.0;
        ans += c_i;
    }
    return ans / n;
}
void write(int n, int graph[N + 4][N + 4], const std::string& path){
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

    dataFile.close();       // 关闭文档
}
void convertVectorToAdj(int n){
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
}
void generateNetwork(int n, int k, double p)
{
    // 构建规则图
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j <= (i + k / 2); ++j)
        {
            int u = i, v = j % N;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
    convertVectorToAdj(n);
    write(n, e, "bef.csv");

    // 随机化重连
    std::random_device rd;// 获取随机设备的种子
    std::mt19937 gen(rd()); // 使用随机种子初始化随机数引擎
    std::uniform_real_distribution<double> disProbability{0.1, 1.0};// 随机生产0~1之间的数
    std::uniform_int_distribution<int> disInteger(0, n - 1);// 随机生成一个整数
    for (int i = 0; i < n; ++i)
    {
        for (auto j: edge[i])
        {
            if (disProbability(gen) < p){
                //随机重连
                int newNeighbor = disInteger(gen);
                // 不能有重边和自环
                if (std::find(edge[i].begin(), edge[i].end(), newNeighbor) == edge[i].end() && i != newNeighbor){
                    /**
                     * 更新操作：将原有的i，j换为i neighbor
                     */
                     // j -> i 取消
                     edge[j].erase(std::find(edge[j].begin(), edge[j].end(), i));
                     edge[i].erase(std::find(edge[i].begin(), edge[i].end(), j));
                     // newNeighbor - i
                     edge[newNeighbor].push_back(i);
                     edge[i].push_back(newNeighbor);
                }
            }
        }
    }
    convertVectorToAdj(n);
}

int main()
{
    int n = N, k = 10;

//    double p = 0.3;
//    generateNetwork(n, k, p);
//    write(n, e, "test.csv");
//    double L = calCharacteristicPathLength(n, e);
//    std::cout << "平均路径长度为" << L << std::endl;
//    double c = cluster_coefficient(n, e);
//    std::cout << "集聚系数为" << c << std::endl;
}