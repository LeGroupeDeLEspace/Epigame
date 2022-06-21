#ifndef GR_VULKAN_INSTANCE_HPP_
#define GR_VULKAN_INSTANCE_HPP_

#include <vulkan/vulkan.hpp>

namespace gr {
    class VulkanInstance {
        public:
            VulkanInstance();
            ~VulkanInstance();

            static std::vector<const char *> getRequiredExtensions();

        private:

            VkInstance instance;
    };
}

#endif