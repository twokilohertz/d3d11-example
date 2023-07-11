cmake_minimum_required(VERSION 3.22)

project(d3d11-example   VERSION 1.0
                        DESCRIPTION "D3D11 Example"
                        LANGUAGES CXX)

add_executable(d3d11-example WIN32 src/main.cpp src/gui.cpp src/dx11_backend.cpp)
target_include_directories(d3d11-example PRIVATE include/)
target_link_libraries(d3d11-example PRIVATE d3d11.lib dxgi.lib)
target_compile_features(d3d11-example PRIVATE cxx_std_17)
target_compile_definitions(d3d11-example    PRIVATE
                                            UNICODE=1
                                            _UNICODE=1
                                            WIN32_LEAN_AND_MEAN=1)
