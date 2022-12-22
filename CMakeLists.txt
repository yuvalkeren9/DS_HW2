cmake_minimum_required(VERSION 3.20)
project(DS2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        #DS2 main.cpp
        wet2util.h
        worldcup23a2.h
        worldcup23a2.cpp
        AVL_tree.h playerHashMap.cpp playerHashMap.h Player.cpp Player.h Team.cpp Team.h Tests/UnionFindTests.cpp playerUnionFind.cpp playerUnionFind.h)
