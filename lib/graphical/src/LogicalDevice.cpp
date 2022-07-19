#include <set>
#include <stdexcept>
#include "LogicalDevice.hpp"
#include "VkConfigConstants.hpp"

namespace gr {

LogicalDevice::LogicalDevice(const PhysicalDevice &physicalDevice)
{
    QueueFamilyIndices indices = physicalDevice.getFamilyQueues();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = 
    {
        indices.graphicsFamily.value(),
        indices.presentFamily.value()
    };
    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(config::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = config::deviceExtensions.data();

    if (config::enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(config::validationLayers.size());
        createInfo.ppEnabledLayerNames = config::validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }
    if (vkCreateDevice(physicalDevice.getDevice(), &createInfo, nullptr, &this->device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device");
    }

    vkGetDeviceQueue(this->device, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily.value(), 0, &this->presentQueue);
}

LogicalDevice::~LogicalDevice()
{
    vkDestroyDevice(this->device, nullptr);
}

const VkDevice &LogicalDevice::getDevice() const
{
    return this->device;
}

VkQueue LogicalDevice::getGraphicsQueue() const
{
    return this->graphicsQueue;
}

VkQueue LogicalDevice::getPresentQueue() const
{
    return this->presentQueue;
}

}