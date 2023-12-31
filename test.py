# import networkx as nx
# import pandas as pd
# import numpy as np
# import matplotlib.pyplot as plt
#
# # A = np.array([[0, 1, 0, 0, 0, 1, 1, 0, 0, 0, ],
# #               [1, 0, 1, 0, 0, 1, 1, 0, 0, 0, ],
# #               [0, 1, 0, 1, 1, 1, 0, 0, 0, 0, ],
# #               [0, 0, 1, 0, 1, 1, 0, 0, 0, 0, ],
# #               [0, 0, 1, 1, 0, 1, 1, 1, 0, 0, ],
# #               [1, 1, 1, 1, 1, 0, 1, 0, 0, 0, ],
# #               [1, 1, 0, 0, 1, 1, 0, 1, 0, 0, ],
# #               [0, 0, 0, 0, 1, 0, 1, 0, 1, 0, ],
# #               [0, 0, 0, 0, 0, 0, 0, 1, 0, 1, ],
# #               [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ]]
# #              )
# # G = nx.from_numpy_array(A)
# # # nx.draw(G)
# # print(nx.closeness_centrality(G))
# df = pd.read_csv("data.txt")
# # print(df)
# x = np.log10(df["p"])
# y = df["l"]
# z = df["c"]
# #
# # fig = plt.figure()
# # ax = fig.add_subplot(111)
# # ax.plot(x, y, '-', label='L(p)/L(0)')
# #
# # ax2 = ax.twinx()
# # ax2.plot(x, z, '-r', label='C(p)/C(0)')
# # fig.legend(loc=1)
#
# # plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
# plt.xlabel('p')
#
# A, = plt.plot(x, y, "bo-", linewidth=2, markersize=12)
# B, = plt.plot(x, z, "gs-", linewidth=2, markersize=12)
#
# plt.show()

# -*- coding: utf-8 -*-
# @Time    : 2018/3/27 18:00
# @Author  : timothy

import scipy.integrate as spi
import numpy as np
import pylab as pl
import networkx as nx
import random as rd


# 初始化
BETA = 0.5  # 感染率
GAMMA = 0.2  # 治愈率
N = 50  # 网络节点数
t_range = np.arange(0, 50, 10e-2)  # 常微分方程迭代步数

# 开始随机选不同两个节点染毒
I = np.zeros(N)
i1 = rd.randint(0, N)
i2 = i1
while i2 == i1:
    i2 = rd.randint(0, N)
I[i1] = 1
I[i2] = 1

# 初始化网络
scale_free_network = nx.random_graphs.barabasi_albert_graph(N, 1)
A = nx.to_numpy_matrix(scale_free_network)


# 常微分方程组
def diff_eqs(X, t):
    Y = np.zeros(N)
    for i in range(N):
        # 节点i邻居的感染情况那个sigma
        neighbor_sum = 0
        for j in range(N):
            neighbor_sum += A[i, j] * X[j]
        Y[i] = (1-X[i]) * BETA * neighbor_sum - GAMMA * X[i]
    return Y


# 开始计算
def run_ode():
    result = spi.odeint(func=diff_eqs, y0=I, t=t_range)
    return result


# 出图
def plot(result):
    pl.plot(result, '-rs', label='I')
    pl.legend(loc=0)
    pl.xlabel('Time')
    pl.ylabel('Ratio')
    pl.show()


def main():
    result = run_ode()
    result_mean = np.mean(result, axis=1)  # 染毒节点平均占比
    plot(result_mean)


if __name__ == '__main__':
    main()
