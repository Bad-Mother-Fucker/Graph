cmake_minimum_required(VERSION 3.17)
project(Graph)

set(CMAKE_CXX_STANDARD 11)

add_executable(Graph main.cpp Graph.h Node.h Exceptions.h TestClass.h)