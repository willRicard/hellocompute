#ifndef HELLO_VK_DEBUG_H
#define HELLO_VK_DEBUG_H

#include <vulkan/vulkan.h>

VkBool32 hello_vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT *message_info, void *user_data);

VkResult hello_vk_debug_init(VkInstance instance);

void hello_vk_debug_quit();

#endif // HELLO_VK_DEBUG_H
