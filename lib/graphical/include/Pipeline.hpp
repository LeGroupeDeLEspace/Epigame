#ifndef GR_PIPELINE_HPP_
#define GR_PIPELINE_HPP_

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"

namespace gr {
    class Pipeline {
        public:
            Pipeline(const LogicalDevice &device, const SwapChain &swapChain);
            ~Pipeline();
        private:
            VkShaderModule loadShader(const std::string &path);

            VkDevice device;

            VkPipeline graphicsPipeline;
            VkPipelineLayout pipelineLayout;
            RenderPass renderPass;
    };
}

#endif