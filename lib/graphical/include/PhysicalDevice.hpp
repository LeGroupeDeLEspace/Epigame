#ifndef GR_PHYSICAL_DEVICE
#define GR_PHYSICAL_DEVICE

#include "VulkanInstance.hpp"
#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"

namespace gr {
    class PhysicalDevice {
        public:
            PhysicalDevice(const VulkanInstance &instance);
            QueueFamilyIndices getFamilyQueues() const;
        private:
            int rateDevice(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
            VkPhysicalDevice device;
            
            static QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);
            static bool queueFamilyPresentSupport(VkPhysicalDevice device, uint32_t i, const VkSurfaceKHR &surface);
            static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, const VkSurfaceKHR &surface);
    };
}

#endif