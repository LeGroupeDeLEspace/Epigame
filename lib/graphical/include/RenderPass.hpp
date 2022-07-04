#ifndef RENDER_PASS_HPP_
#define RENDER_PASS_HPP_

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"

namespace gr {
    class RenderPass {
        public:
            RenderPass(const LogicalDevice &device, const SwapChain &swapChain);
            ~RenderPass();

        private:
            VkRenderPass renderPass;
            const VkDevice device;
    };
}

#endif