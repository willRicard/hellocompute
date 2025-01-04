#include "vk_instance.h"

#include <vulkan/vulkan.h>

#include "vk_debug.h"
#include "vulkan/vulkan_core.h"

static const char *kAppVkExtensions[] = {
    "VK_EXT_debug_utils",
#ifdef __APPLE__
    "VK_KHR_portability_enumeration",
#endif
};

static VkInstance instance = VK_NULL_HANDLE;

VkResult hello_vk_instance_create() {
  static const char *kAppName = "Hello Add (Vulkan)";
  static const char *kAppLayers[] = {"VK_LAYER_KHRONOS_validation"};

  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = kAppName;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_MAKE_VERSION(1, 2, 283);

  VkDebugUtilsMessengerCreateInfoEXT debug_info = {};
  debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
  debug_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_info.pfnUserCallback = hello_vk_debug_callback;

  VkInstanceCreateInfo instance_info = {};
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pNext = &debug_info;
#ifdef __APPLE__
  instance_info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
  instance_info.pApplicationInfo = &app_info;
  instance_info.enabledLayerCount = 1;
  instance_info.ppEnabledLayerNames = kAppLayers;
  instance_info.enabledExtensionCount = 2;
  instance_info.ppEnabledExtensionNames = kAppVkExtensions;

  return vkCreateInstance(&instance_info, NULL, &instance);
}

VkInstance hello_vk_instance_get() { return instance; }

void hello_vk_instance_destroy() {
  if (instance != VK_NULL_HANDLE) {
    vkDestroyInstance(instance, NULL);
    instance = VK_NULL_HANDLE;
  }
}
