#ifndef GR_PIPELINE_HPP_
#define GR_PIPELINE_HPP_

#include <vector>
#include <string>
#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "PhysicalDevice.hpp"
#include "VulkanInstance.hpp"

namespace gr {
    class Pipeline {
        public:
            Pipeline(VulkanInstance &instance, const LogicalDevice &device, SwapChain &swapChain, const PhysicalDevice &physicalDevice);
            ~Pipeline();
            void drawFrame();
        private:
            VkShaderModule loadShader(const std::string &path);
            void initFrameBuffers(const SwapChain &swapChain);
            void initCommandPool(const PhysicalDevice &physicalDevice);
            void initCommandBuffer(const SwapChain &swapChain);
            void initSemaphores();
            void initVbuffer();
            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
            void createGraphicsPipeline();
            void swapChainRecreation();
            void cleanPipeline();
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


            const LogicalDevice &device;
            SwapChain &swapChain;
            const PhysicalDevice &physicalDevice;
            VulkanInstance &instance;

            VkPipeline graphicsPipeline;
            VkPipelineLayout pipelineLayout;
            RenderPass renderPass;
            std::vector<VkFramebuffer> frambuffers;

            VkBuffer vbuffer;   //maybe TODO createClass
            VkDeviceMemory vbufferMemory;

            VkCommandPool commandPool;  //TODO createClass
            VkCommandBuffer commandBuffer;

            int currentFrame;

            std::vector<VkSemaphore> imageAvailableSemaphore;
            std::vector<VkSemaphore> renderFinishedSemaphore;
            std::vector<VkFence> inFlightFence;
            std::vector<VkFence> imagesInFlight;
    };
}

#endif