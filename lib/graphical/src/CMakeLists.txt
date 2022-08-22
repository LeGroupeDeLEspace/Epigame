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
    Pipeline.cpp
    Vertex.cpp
    Buffer.cpp
    ShapesManager.cpp
    ShapeBase.cpp
    RectangleShape.cpp
    CircleShape.cpp
    GBuffer.cpp
)