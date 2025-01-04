#include <stdio.h>
#include <stdlib.h>

#include "vk_debug.h"
#include "vk_device.h"
#include "vk_instance.h"
#include "vulkan/vulkan_core.h"

static void cleanup() {
  hello_vk_debug_quit();
  hello_vk_device_destroy();
  hello_vk_instance_destroy();
}

int main(int argc, char **argv) {
  VkResult result = hello_vk_instance_create();
  if (result != VK_SUCCESS) {
    return EXIT_FAILURE;
  }

  atexit(cleanup);

  result = hello_vk_debug_init(hello_vk_instance_get());
  if (result != VK_SUCCESS) {
    return EXIT_FAILURE;
  }

  result = hello_vk_device_create(hello_vk_instance_get());
  if (result != VK_SUCCESS) {
    return EXIT_FAILURE;
  }

  VkCommandBuffer command_buffer = VK_NULL_HANDLE;

  VkCommandBufferAllocateInfo cmdbuf_info = {};
  cmdbuf_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdbuf_info.commandPool = hello_vk_device_get_command_pool();
  cmdbuf_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmdbuf_info.commandBufferCount = 1;
  result = vkAllocateCommandBuffers(hello_vk_device_get(), &cmdbuf_info,
                                    &command_buffer);
  if (result != VK_SUCCESS) {
    return EXIT_FAILURE;
  }

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

  result = vkBeginCommandBuffer(command_buffer, &begin_info);
  if (result != VK_SUCCESS) {
    return EXIT_FAILURE;
  }

  vkCmdDispatch(command_buffer, 1 << 20, 1, 1);

  printf("All OK\n");

  vkFreeCommandBuffers(hello_vk_device_get(),
                       hello_vk_device_get_command_pool(), 1, &command_buffer);
  command_buffer = VK_NULL_HANDLE;

  cleanup();

  return EXIT_SUCCESS;
}
