#ifndef GR_SWAP_CHAIN_HPP_
#define GR_SWAP_CHAIN_HPP_

#include <vector>
#include "PhysicalDevice.hpp"

namespace gr {

    class SwapChain {
        public:
            SwapChain(VkDevice device, const PhysicalDevice &physicalDevice, const VulkanInstance &instance, uint32_t width, uint32_t height);
            ~SwapChain();

            void recreate();

            const VkFormat &getImageFormat() const;
            const VkExtent2D &getExtent() const;
            const std::vector<VkImageView> &getViews() const;
            const VkSwapchainKHR &getSwapChain() const;
            const std::vector<VkImage> &getImages() const;
        private:
            void createImageViews();

            VkDevice device;
            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkImageView> swapChainImageViews;
    };

}

#endif