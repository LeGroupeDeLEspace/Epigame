cmake_minimum_required(VERSION 3.13.0)

target_sources(graphRender PRIVATE
    Graphics.cpp
    VulkanInstance.cpp
    VkConfigConstants.cpp
    ValidationLayer.cpp
    WindowHandler.cpp
    PhysicalDevice.cpp
    QueueFamilyIndices.cpp
    SwapChainSupportDetails.cpp
    LogicalDevice.cpp
    SwapChain.cpp
    RenderPass.cpp
)