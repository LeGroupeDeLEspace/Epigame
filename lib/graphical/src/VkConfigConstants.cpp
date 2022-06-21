#include <vulkan/vulkan.hpp>
#include "VkConfigConstants.hpp"

const char* applicationName = "jeudelespace";

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",
};
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const bool enableValidationLayers = true;

