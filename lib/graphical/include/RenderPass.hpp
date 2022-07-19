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

            void recreate(const SwapChain &swapChain);
        private:

            void initPass(const SwapChain &swapChain);
            VkRenderPass renderPass;
            const VkDevice device;
    };
}

#endif