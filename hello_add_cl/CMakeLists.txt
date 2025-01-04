cmake_minimum_required(VERSION 3.10)

project(HelloCL)

find_package(OpenCL REQUIRED)

add_executable(hello_add_cl
  src/cl_buffer.c
  src/cl_context.c
  src/cl_device.c
  src/cl_error.c
  src/cl_kernel.c
  src/cl_platform.c
  src/cl_program.c
  src/cl_queue.c
  src/main.c
)

target_link_libraries(hello_add_cl PUBLIC OpenCL::OpenCL)
