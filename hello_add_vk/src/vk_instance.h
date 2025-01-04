#ifndef HELLO_VK_INSTANCE_H
#define HELLO_VK_INSTANCE_H

#include <vulkan/vulkan.h>

VkResult hello_vk_instance_create();

VkInstance hello_vk_instance_get();

void hello_vk_instance_destroy();

#endif // HELLO_VK_INSTANCE_H
