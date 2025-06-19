#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

namespace Raze {

class VulkanInstance {
public:
  VulkanInstance();
  ~VulkanInstance();

  VkInstance get() const {
    return m_instance;
  }

private:
  void createInstance();
  std::vector<const char*> getRequiredExtensions() const;

  VkInstance m_instance{};

};

} // namespace Raze

#endif // VULKANINSTANCE_H


