cmake_minimum_required(VERSION 3.26)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp
        main.cpp
        topologyProperties.h
        utils.cpp
        utils.h
        graph.h
        graph.cpp
        topologyProperties.cpp
#        centrality.cpp
#        centrality.h
        network_model.cpp
        network_model.h
        centrality.cpp
)
