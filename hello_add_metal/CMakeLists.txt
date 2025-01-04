cmake_minimum_required(VERSION 3.10)

project(hello_add_metal)

add_executable(hello_add_metal src/main.m)

target_link_libraries(hello_add_metal PUBLIC "-framework MetalKit -framework Metal -framework AppKit -framework Foundation")
