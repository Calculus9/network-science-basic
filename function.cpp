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
        vis[mn_i] = 1; // 2  3 6 4 11 9
        // 根据新的节点来更新其他所有节点的距离
        for (int j = 0; j < n; ++j)
        {
            if (e[mn_i][j])
                dis[j] = std::min(dis[j], dis[mn_i] + e[mn_i][j]);
        }
    }
    return dis;
}

/**
* 网络模型
*/
//环状最近邻耦合网络
std::vector<std::vector<int>> generateRingNearestNeighborCoupledNet(int n, int k){
    std::vector<std::vector<int>> edge(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j <= (i + k / 2); ++j)
        {
            int u = i, v = j % n;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
    return edge;
}
// WS小世界网络
void generateWSSmallWorldNetwork(int n, int k, double p)
{
    // 构建规则图
    std::vector<std::vector<int>> edge = generateRingNearestNeighborCoupledNet(n,k);
    int** preGraph = convertVectorToAdj(n, edge);
    write(n, preGraph, "bef.csv");

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
    int** swGraph = convertVectorToAdj(n, edge);
    write(n, swGraph, "test.csv");
}


/**
* 工具类
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
 * 转换vector为邻接矩阵
 * @param n 节点数目
 * @param edge 待转化的vector
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
 * 计算度值
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return 度值数组
 */
int*calDegree(int** graph, int n){
    int* degree = new int[n + 5];
    for (int i = 0; i < n; ++i)
    {
        degree[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            degree[i] += graph[i][j] == 1;
        }
    }
    return degree;
}

/**
 * 计算度中心性
 * @param degree 度值数组
 * @param n 节点数目
 * @return 返回各个节点的度中心性列表
 */
double* calDegreeCentrality(int* degree, int n){
    double* degreeCentrality = new double[n + 5];
    for (int i = 0; i < n; ++i)
    {
        degreeCentrality[i] = degree[i] * 1.0 / (n - 1);
    }
    return degreeCentrality;
}
// 计算节点对之间的最短路径数量
std::map<int, int>calShortestPathCnts(int n, int** graph, int s){
    std::vector<std::vector<int>> edge = convertAdjToVec(n, graph);
    // BFS计算其最短路径
    std::queue<int> q;//进行bfs
    bool vis[n + 5];// 是否访问过
    std::map<int, std::string> mp;//保存节点s到节点t的最短路径
    q.push(s);
    vis[s] = true;
    while (!q.empty()){
        int top = q.front(); q.pop();

    }
}

/**
 * 计算介数中心性
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return
 */
double* calBetweenessCentrality(int** graph, int n){
    calShortestPathCnts(n, graph, 0);
}
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
/**
 * 计算i节点的所有路径。
 * @return i节点的路径和
 */
double calD_i(int n, std::vector<std::vector<int>> edge){
    double cc = 0.0, res = 0.0;
    double* d_i = new double [n + 5];
    for (int i = 0; i < n; ++i)
    {
        // 求得节点node到其他节点的距离为BFS
        std::map<int, int>mp = BFS(i, edge);
        cc = 0.0;
        for(auto x: mp){
            cc += x.second;
        }
        d_i[i] = (n - 1) / cc;
        res += d_i[i];
        std::cout << d_i[i] << std::endl;
    }
    return res / n;
}
/**
 * 计算接近中心性
 * @param graph 邻接矩阵
 * @param n 节点数目
 * @return
 */
double* calClosenessCentrality(int** graph, int n){
    std::vector<std::vector<int>> edge = convertAdjToVec(n, graph, false);
    double* cc_i = new double [n + 5];
    std::cout << calD_i(n, edge) << " ";
}

/**
 * 平均集聚系数
 * @param n
 * @param graph
 * @return
 */

double clusterCoefficient(int n, std::vector<std::vector<int>> v, int node)
{
    double res = 0.0;
    int size = v[node].size();
    for(auto x: v[node]){
        for(auto y: v[node]){
            if (x != y && std::find(v[x].begin(), v[x].end(), y) != v[x].end() &&
                std::find(v[y].begin(), v[y].end(), x) != v[y].end()
                ){
                res += 1.0;
            }
        }
    }

    return res * 1.0 ? res / ((size - 1) * size) : 0;
}

double averageClusterCoefficient(int n, int **graph){
    //初始化
    double res = 0.0;
    std::vector<std::vector<int>> v = convertAdjToVec(n, graph, false);
    std::vector<std::vector<int>>::iterator iter;
    for (int i = 0; i < n; ++i)
    {
        double c_i = clusterCoefficient(n, v, i);
        std::cout << c_i << std::endl;
        res += 1.0 * c_i;
    }
    return res * 1.0 / n;
}


/**
 * 求平均路径长度
 */
double calCharacteristicPathLength(int n, int** graph){
    int path[n+5][n + 5];
    std::queue<int> q;
    bool vis[n + 5];
    memset(path, 99 , sizeof path);
    int step = 1;
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
