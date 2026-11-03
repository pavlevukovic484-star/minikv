cmake_minimum_required(VERSION 3.12)
project(MiniKVStore CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)


add_executable(minikv
    src/main.cpp
    src/store.cpp
)


target_link_directories(minikv PRIVATE required)