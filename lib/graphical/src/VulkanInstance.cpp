#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "VulkanInstance.hpp"
#include "VkConfigConstants.hpp"
#include "ValidationLayer.hpp"

namespace gr {

static VkApplicationInfo createAppInfo()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = gr::config::applicationName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;
    return appInfo;
}

void VulkanInstance::createInstance()
{
    VkApplicationInfo appInfo = createAppInfo();

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char *> extensions = getRequiredExtensions();

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (gr::config::enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(gr::config::validationLayers.size());
        createInfo.ppEnabledLayerNames = gr::config::validationLayers.data();

        ValidationLayer::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = &debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance)) {
        throw std::runtime_error("failed to create instance");
    }
}

void VulkanInstance::createSurface(GLFWwindow *window)
{
    if (glfwCreateWindowSurface(this->instance, window, nullptr, &this->surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }
}

VulkanInstance::VulkanInstance(GLFWwindow *window) : validationLayer(nullptr)
{
    this->createInstance();
    this->validationLayer = new ValidationLayer(this->instance);
    this->createSurface(window);
}

VulkanInstance::~VulkanInstance()
{
    vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
    delete this->validationLayer;
    vkDestroyInstance(this->instance, nullptr);
}

const VkInstance &VulkanInstance::getInstance() const
{
    return this->instance;
}

const VkSurfaceKHR &VulkanInstance::getSurface() const
{
    return this->surface;
}

std::vector<const char *> VulkanInstance::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (gr::config::enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

}