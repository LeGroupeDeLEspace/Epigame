#include <vulkan/vulkan.h>
#include "VkConfigConstants.hpp"

namespace gr {
namespace config {

const char* applicationName = "jeudelespace";

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",
};
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const bool enableValidationLayers = true;

const int maxFrameInFlight = 2;

}
}