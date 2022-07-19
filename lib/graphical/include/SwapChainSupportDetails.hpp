#ifndef GR_SWAP_CHAIN_SUPPORT_DETAILS_HPP_
#define GR_SWAP_CHAIN_SUPPORT_DETAILS_HPP_

#include <vulkan/vulkan.h>
#include <vector>

namespace gr {

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;

        bool isComplete() const;
        VkSurfaceFormatKHR chooseSwapSurfaceFormat() const;
        VkPresentModeKHR chooseSwapPresentMode() const;
        VkExtent2D chooseSwapExtent(uint32_t width, uint32_t height) const;
    };

}

#endif