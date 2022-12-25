cmake_minimum_required(VERSION 3.24)
project(infra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -lpthread -Wno-deprecated")

link_directories(
        ${PROJECT_SOURCE_DIR}/lib
)

add_executable(infra infra.cpp)
