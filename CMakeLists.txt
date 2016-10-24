cmake_minimum_required(VERSION 3.3)
project(zadacha1var4_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(SOURCE_FILES main.cpp coefficient.cpp coefficient.h gasTask.cpp gasTask.h Equation.cpp Equation.h appPoint.cpp appPoint.h ListPoints.cpp ListPoints.h mytypes.h)
add_executable(zadacha1var4_4 ${SOURCE_FILES})