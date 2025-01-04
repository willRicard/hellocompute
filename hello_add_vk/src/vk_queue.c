#include "vk_queue.h"
#include "vulkan/vulkan_core.h"

uint32_t hello_vk_queue_select(VkPhysicalDevice physical_device) {
  uint32_t queue_family_count = 4;
  VkQueueFamilyProperties queue_infos[4] = {};
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count,
                                           queue_infos);

  for (uint32_t i = 0; i < queue_family_count; ++i) {
    queue_infos[i].queueFlags &= VK_QUEUE_COMPUTE_BIT;
    return i;
  }
  return -1;
}
