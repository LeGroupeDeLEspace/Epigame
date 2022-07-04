#ifndef GR_RENDER_PASS_HPP_
#define GR_RENDER_PASS_HPP_

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"

namespace gr {
    class RenderPass {
        public:
            RenderPass(const LogicalDevice &device, const SwapChain &swapChain);
            ~RenderPass();

            const VkRenderPass &getPass() const;
        private:
            VkRenderPass renderPass;
            const VkDevice device;
    };
}

#endif