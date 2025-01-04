#ifndef HELLO_VK_DEVICE_H
#define HELLO_VK_DEVICE_H

#include <vulkan/vulkan.h>

VkResult hello_vk_device_create(VkInstance instance);

VkDevice hello_vk_device_get();

VkPhysicalDevice hello_vk_device_get_physical();

uint32_t hello_vk_device_get_queue_family();

VkQueue hello_vk_device_get_queue();

VkCommandPool hello_vk_device_get_command_pool();

VkFence hello_vk_device_get_fence();

void hello_vk_device_destroy();

#endif // HELLO_VK_DEVICE_H
