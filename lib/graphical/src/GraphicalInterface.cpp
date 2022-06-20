#include <iostream>
#include <vector>
#include "graphRender.hpp"

const int WIDTH = 600;
const int HEIGHT = 500;

GraphicalInterface::GraphicalInterface() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);
}

GraphicalInterface::~GraphicalInterface() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

std::vector<const char *> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    return extensions;
}

void GraphicalInterface::test()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanTest";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char *> extensions = getRequiredExtensions();

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = 0;
    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS) {
        uint32_t physicalDeviceCount;
        vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
        std::vector<VkPhysicalDevice> devices;
        devices.resize(physicalDeviceCount);
        vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices.data());
        std::cout << "devices: " << physicalDeviceCount << std::endl;
        for (auto device : devices) {
            VkPhysicalDeviceProperties prop;
            vkGetPhysicalDeviceProperties(device, &prop);
            std::cout << prop.deviceName << std::endl;
        }
        //test
    }
    else {
        std::cerr << "aled" << std::endl;
    }


    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}