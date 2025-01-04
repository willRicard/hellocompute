cmake_minimum_required(VERSION 3.10)

project(hello_add_vk)

find_package(Vulkan REQUIRED)

add_executable(hello_add_vk
  src/main.c
  src/vk_debug.c
  src/vk_device.c
  src/vk_instance.c
  src/vk_queue.c
)

target_link_libraries(hello_add_vk PUBLIC Vulkan::Vulkan)
