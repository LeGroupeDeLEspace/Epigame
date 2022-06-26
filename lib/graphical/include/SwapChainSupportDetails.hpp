#ifndef GR_SWAP_CHAIN_SUPPORT_DETAILS_HPP_
#define GR_SWAP_CHAIN_SUPPORT_DETAILS_HPP_

#include <vulkan/vulkan.hpp>

namespace gr {

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;

        bool isComplete() const;
    };

}

#endif