cmake_minimum_required(VERSION 3.10)

project(HelloCUDA LANGUAGES CXX CUDA)

add_executable(hello_add_cpu src/main_cpu.cpp)

add_executable(hello_add_gpu src/main.cu)
