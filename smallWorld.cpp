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
    // ��ÿ���ڵ�����ҵ����Ӧ����Сֵ
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
                        // ȡ��Сֵ�������ٴ��ҵ�ʱ���޸�����ط�
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
    //��ʼ��
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
    // ��csv�ĵ���д������
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
            dataFile << graph[i][j] << ",";          // д������
        }
        dataFile <<  std::endl;                       // ����
    }

    dataFile.close();       // �ر��ĵ�
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
    // ��������ͼ
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

    // ���������
    std::random_device rd;// ��ȡ����豸������
    std::mt19937 gen(rd()); // ʹ��������ӳ�ʼ�����������
    std::uniform_real_distribution<double> disProbability{0.1, 1.0};// �������0~1֮�����
    std::uniform_int_distribution<int> disInteger(0, n - 1);// �������һ������
    for (int i = 0; i < n; ++i)
    {
        for (auto j: edge[i])
        {
            if (disProbability(gen) < p){
                //�������
                int newNeighbor = disInteger(gen);
                // �������رߺ��Ի�
                if (std::find(edge[i].begin(), edge[i].end(), newNeighbor) == edge[i].end() && i != newNeighbor){
                    /**
                     * ���²�������ԭ�е�i��j��Ϊi neighbor
                     */
                     // j -> i ȡ��
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
//    std::cout << "ƽ��·������Ϊ" << L << std::endl;
//    double c = cluster_coefficient(n, e);
//    std::cout << "����ϵ��Ϊ" << c << std::endl;
}