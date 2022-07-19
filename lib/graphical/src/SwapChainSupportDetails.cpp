#include "SwapChainSupportDetails.hpp"

namespace gr {

bool SwapChainSupportDetails::isComplete() const
{
    return !this->formats.empty() && !this->presentModes.empty();
}

VkSurfaceFormatKHR SwapChainSupportDetails::chooseSwapSurfaceFormat() const
{
    for (const VkSurfaceFormatKHR &format : this->formats) {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB &&
        format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }
    return this->formats[0];
}

VkPresentModeKHR SwapChainSupportDetails::chooseSwapPresentMode() const
{
    for (const auto& availablePresentMode : this->presentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChainSupportDetails::chooseSwapExtent(uint32_t width, uint32_t height) const
{
    if (this->capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent{width, height};

        //TODO adapt from course page 154 using WindowHandler

        actualExtent.width = std::max(this->capabilities.minImageExtent.width, std::min(this->capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(this->capabilities.minImageExtent.height, std::min(this->capabilities.maxImageExtent.height, actualExtent.height));
        return actualExtent;
    }
}

}