#include "vk_device.h"

#include <vulkan/vulkan.h>

#include "vk_queue.h"

static const char *kAppVkDeviceExtensions[] = {"VK_KHR_portability_subset"};

static VkDevice device = VK_NULL_HANDLE;
static VkPhysicalDevice physical_device = VK_NULL_HANDLE;
static uint32_t queue_family = 0;

static VkQueue queue = NULL;

static VkCommandPool command_pool = VK_NULL_HANDLE;

static VkFence fence = VK_NULL_HANDLE;

VkResult hello_vk_device_create(VkInstance instance) {
  uint32_t dev_count = 1;
  VkResult result =
      vkEnumeratePhysicalDevices(instance, &dev_count, &physical_device);
  if (result != VK_SUCCESS && result != VK_INCOMPLETE) {
    return result;
  }

  queue_family = hello_vk_queue_select(physical_device);

  static const float kQueuePriority[] = {1.0f};

  VkDeviceQueueCreateInfo queue_info = {};
  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.flags = 0;
  queue_info.queueFamilyIndex = queue_family;
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = kQueuePriority;

  VkDeviceCreateInfo device_info = {};
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.queueCreateInfoCount = 1;
  device_info.pQueueCreateInfos = &queue_info;
  device_info.enabledExtensionCount = 1;
  device_info.ppEnabledExtensionNames = kAppVkDeviceExtensions;

  result = vkCreateDevice(physical_device, &device_info, NULL, &device);
  if (result != VK_SUCCESS) {
    return result;
  }

  vkGetDeviceQueue(device, queue_family, 0, &queue);

  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pool_info.queueFamilyIndex = queue_family;
  result = vkCreateCommandPool(device, &pool_info, NULL, &command_pool);
  if (result != VK_SUCCESS) {
    return result;
  }

  VkFenceCreateInfo fence_info = {};
  fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  return vkCreateFence(device, &fence_info, NULL, &fence);
}

VkDevice hello_vk_device_get() { return device; }

VkPhysicalDevice hello_vk_device_get_physical() { return physical_device; }

uint32_t hello_vk_device_get_queue_family() { return queue_family; }

VkQueue hello_vk_device_get_queue() { return queue; }

VkCommandPool hello_vk_device_get_command_pool() { return command_pool; }

VkFence hello_vk_device_get_fence() { return fence; }

void hello_vk_device_destroy() {
  if (device == VK_NULL_HANDLE) {
    return;
  }
  vkDeviceWaitIdle(device);
  if (fence != VK_NULL_HANDLE) {
    vkDestroyFence(device, fence, NULL);
    fence = VK_NULL_HANDLE;
  }
  if (command_pool != VK_NULL_HANDLE) {
    vkDestroyCommandPool(device, command_pool, NULL);
    command_pool = VK_NULL_HANDLE;
  }
  queue = VK_NULL_HANDLE;
  vkDestroyDevice(device, NULL);
  device = VK_NULL_HANDLE;
}
