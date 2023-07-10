cmake_minimum_required(VERSION 3.22)

project(d3d11-example   VERSION 1.0
                        DESCRIPTION "D3D11 Example"
                        LANGUAGES CXX)

add_executable(d3d11-example WIN32 src/main.cpp)
target_include_directories(d3d11-example PRIVATE include)
target_compile_features(d3d11-example PRIVATE cxx_std_17)
add_compile_definitions(UNICODE=1 _UNICODE=1)
