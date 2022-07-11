#ifndef GR_PIPELINE_HPP_
#define GR_PIPELINE_HPP_

#include <vector>
#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "PhysicalDevice.hpp"

namespace gr {
    class Pipeline {
        public:
            Pipeline(const LogicalDevice &device, const SwapChain &swapChain, const PhysicalDevice &physicalDevice);
            ~Pipeline();
            void drawFrame();
        private:
            VkShaderModule loadShader(const std::string &path);
            void initFrameBuffers(const SwapChain &swapChain);
            void initCommandPool(const PhysicalDevice &physicalDevice);
            void initCommandBuffer(const SwapChain &swapChain);
            void initSemaphores();
            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

            const LogicalDevice &device;
            const SwapChain &swapChain;
            const PhysicalDevice &physicalDevice;

            VkPipeline graphicsPipeline;
            VkPipelineLayout pipelineLayout;
            RenderPass renderPass;
            std::vector<VkFramebuffer> frambuffers;
            VkCommandPool commandPool;  //TODO createClass
            VkCommandBuffer commandBuffer;

            VkSemaphore imageAvailableSemaphore;
            VkSemaphore renderFinishedSemaphore;
    };
}

#endif