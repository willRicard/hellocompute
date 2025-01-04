#include "vk_debug.h"

#include <stdio.h>

#include "vk_instance.h"

static PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT =
    NULL;

static PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT =
    NULL;

static VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;

VkBool32 hello_vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT *message_info, void *user_data) {
  fprintf(stderr, "%s %s\n", message_info->pMessageIdName,
          message_info->pMessage);
  return VK_FALSE;
}

VkResult hello_vk_debug_init(VkInstance instance) {
  if (_vkCreateDebugUtilsMessengerEXT == NULL) {
    _vkCreateDebugUtilsMessengerEXT =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkCreateDebugUtilsMessengerEXT");
    if (_vkCreateDebugUtilsMessengerEXT == NULL) {
      return VK_ERROR_FEATURE_NOT_PRESENT;
    }
  }
  if (_vkDestroyDebugUtilsMessengerEXT == NULL) {
    _vkDestroyDebugUtilsMessengerEXT =
        (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkDestroyDebugUtilsMessengerEXT");
    if (_vkDestroyDebugUtilsMessengerEXT == NULL) {
      return VK_ERROR_FEATURE_NOT_PRESENT;
    }
  }

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

  return _vkCreateDebugUtilsMessengerEXT(instance, &debug_info, NULL,
                                         &messenger);
}

void hello_vk_debug_quit() {
  if (messenger != VK_NULL_HANDLE) {
    _vkDestroyDebugUtilsMessengerEXT(hello_vk_instance_get(), messenger, NULL);
    messenger = VK_NULL_HANDLE;
  }
}
