#include <System.hpp>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstring>
#include <algorithm>

#include "Pipeline.hpp"
#include "VkConfigConstants.hpp"
#include "WindowHandler.hpp"
#include "Vertex.hpp"

// static const std::vector<gr::Vertex> vertices = {   //tmp test data
//     {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//     {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
//     {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    
//     {{1.f, -0.5f}, {0.0f, 0.0f, 1.0f}},
//     {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
//     {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
// };

// static const std::vector<gr::Vertex> vertices2 = {
//     {{-1.f, -0.5f}, {0.0f, 0.0f, 1.0f}},
//     {{0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}},
//     {{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
// };

namespace gr {

void Pipeline::createGraphicsPipeline()
{
    VkShaderModule vertShaderModule = this->loadShader(su::System::resolvePath(std::vector<std::string>{
        "shaders", "base.vert.spv",
    }));
    VkShaderModule fragShaderModule = this->loadShader(su::System::resolvePath(std::vector<std::string>{
        "shaders", "base.frag.spv",
    }));

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {
        vertShaderStageInfo, fragShaderStageInfo,
    };

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescription = Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescription.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescription.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) swapChain.getExtent().width;
    viewport.height = (float) swapChain.getExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};

    scissor.offset = {0, 0};
    scissor.extent = swapChain.getExtent();

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;
    rasterizer.depthBiasClamp = 0.0f;
    rasterizer.depthBiasSlopeFactor = 0.0f;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = 
        VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    // VkDynamicState dynamicStates[] = {   dynamique
    //     VK_DYNAMIC_STATE_VIEWPORT,
    //     VK_DYNAMIC_STATE_LINE_WIDTH,
    // };

    // VkPipelineDynamicStateCreateInfo dynamicState{};
    // dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    // dynamicState.dynamicStateCount = 2;
    // dynamicState.pDynamicStates = dynamicStates;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};

    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(this->device.getDevice(), &pipelineLayoutInfo, nullptr, &this->pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;

    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr;
    pipelineInfo.layout = this->pipelineLayout;
    pipelineInfo.renderPass = this->renderPass.getPass();
    pipelineInfo.subpass = 0;
    
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(this->device.getDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(this->device.getDevice(), vertShaderModule, nullptr);
    vkDestroyShaderModule(this->device.getDevice(), fragShaderModule, nullptr);

}

Pipeline::Pipeline(VulkanInstance &instance, const LogicalDevice &device, SwapChain &swapChain, const PhysicalDevice &physicalDevice) : device(device), swapChain(swapChain), physicalDevice(physicalDevice), renderPass(device, swapChain), instance(instance)
{
    this->createGraphicsPipeline();
    this->initFrameBuffers(this->swapChain);
    this->initCommandPool(this->physicalDevice);
    this->initVbuffer();
    this->initCommandBuffer(this->swapChain);
    this->initSemaphores();
    this->currentFrame = 0;

}

Pipeline::~Pipeline()
{
    for (auto it : this->inFlightFence) {
        vkDestroyFence(this->device.getDevice(), it, nullptr);
    }
    for (auto it : this->renderFinishedSemaphore) {
        vkDestroySemaphore(this->device.getDevice(), it, nullptr);
    }
    for (auto it : this->imageAvailableSemaphore) {
        vkDestroySemaphore(this->device.getDevice(), it, nullptr);
    }
    this->cleanPipeline();
    vkDestroyCommandPool(this->device.getDevice(), this->commandPool, nullptr);
}

void Pipeline::initVbuffer()
{
    // Buffer &test = this->newBuffer(vertices.size());
    // test.copyData(vertices.data());
}

void Pipeline::cleanPipeline()
{
    vkFreeCommandBuffers(this->device.getDevice(), commandPool, 1, &this->commandBuffer);

    for (auto it : this->frambuffers) {
        vkDestroyFramebuffer(this->device.getDevice(), it, nullptr);
    }
    vkDestroyPipeline(this->device.getDevice(), this->graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(this->device.getDevice(), this->pipelineLayout, nullptr);
}

VkShaderModule Pipeline::loadShader(const std::string &path)
{
    std::vector<char> code = su::System::readFile(path);

    VkShaderModuleCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
    VkShaderModule result;

    if (vkCreateShaderModule(this->device.getDevice(), &createInfo, nullptr, &result) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module");
    }
    return result;
}

void Pipeline::initFrameBuffers(const SwapChain &swapChain)
{
    size_t n_buffers = swapChain.getViews().size();
    this->frambuffers.resize(n_buffers);

    for (size_t i = 0; i < n_buffers; i++) {
        VkImageView attachments[] = {   // peut être à simplifier ? (VkImageView *attachments = &swapChain[i])
            swapChain.getViews()[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = this->renderPass.getPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChain.getExtent().width;
        framebufferInfo.height = swapChain.getExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device.getDevice(), &framebufferInfo, nullptr, &this->frambuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer");
        }
    }
}

void Pipeline::initCommandPool(const PhysicalDevice &physicalDevice)
{
    QueueFamilyIndices queueFamilyIndices = physicalDevice.getFamilyQueues();

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(this->device.getDevice(), &poolInfo, nullptr, &this->commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool");
    }
}

void Pipeline::initCommandBuffer(const SwapChain &swapChain)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(this->device.getDevice(), &allocInfo, &this->commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffers");
    }
}

void Pipeline::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("help follow up in 30 min");
    }

    //TODO implem to renderPass class
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = this->renderPass.getPass();
    renderPassInfo.framebuffer = this->frambuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = this->swapChain.getExtent();


    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    // VkBuffer vertexBuffers[] = {this->buffer.getBuffer()};
    // VkDeviceSize offsets[] = {0};
    // vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    // vkCmdDraw(commandBuffer, vertices.size(), 1, 0, 0);
    
    // VkBuffer vertexBuffers2[] = {this->buffer2.getBuffer()};
    // vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers2, offsets);
    // vkCmdDraw(commandBuffer, vertices2.size(), 1, 0, 0);

    for (auto &it : this->buffers2d) {
        it.draw(commandBuffer);
    }
    
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("20 min");
    }

}

void Pipeline::drawFrame()
{
    vkWaitForFences(this->device.getDevice(), 1, &inFlightFence[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(this->device.getDevice(), this->swapChain.getSwapChain(), UINT64_MAX, this->imageAvailableSemaphore[this->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->device.getDevice(), 1, &this->imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        // std::cout << "waiting: " << this->imagesInFlight[imageIndex] << "(" << imageIndex << "/" << currentFrame << ")" << std::endl;
    }
    this->imagesInFlight[imageIndex] = this->inFlightFence[currentFrame];
    // std::cout << "set: " << this->imagesInFlight[imageIndex] << "(" << imageIndex << "/" << currentFrame << ")" << std::endl;

    vkResetCommandBuffer(this->commandBuffer, 0);
    this->recordCommandBuffer(this->commandBuffer, imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {this->imageAvailableSemaphore[this->currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->commandBuffer;

    VkSemaphore signalSemaphores[] = {this->renderFinishedSemaphore[this->currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(this->device.getDevice(), 1, &inFlightFence[currentFrame]);

    if (vkQueueSubmit(this->device.getGraphicsQueue(), 1, &submitInfo, inFlightFence[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("8 min");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {this->swapChain.getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;
    VkResult result = vkQueuePresentKHR(this->device.getPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        this->swapChainRecreation();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image");
    }

    this->currentFrame = (currentFrame + 1) % config::maxFrameInFlight;

    vkQueueWaitIdle(this->device.getPresentQueue());
}

Buffer &Pipeline::newBuffer(size_t nvertex, size_t nindex)
{
    this->buffers2d.push_back(Buffer(this->device, this->physicalDevice, nvertex, nindex));
    return this->buffers2d.back();
}

void Pipeline::initSemaphores()
{
    this->imageAvailableSemaphore.resize(config::maxFrameInFlight);
    this->renderFinishedSemaphore.resize(config::maxFrameInFlight);
    this->inFlightFence.resize(config::maxFrameInFlight);
    this->imagesInFlight.resize(this->swapChain.getImages().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (int i = 0; i < config::maxFrameInFlight; i++) {

        if (vkCreateSemaphore(this->device.getDevice(), &semaphoreInfo, nullptr, &this->imageAvailableSemaphore[i]) != VK_SUCCESS ||
            vkCreateSemaphore(this->device.getDevice(), &semaphoreInfo, nullptr, &this->renderFinishedSemaphore[i]) != VK_SUCCESS ||
            vkCreateFence(this->device.getDevice(), &fenceInfo, nullptr, &this->inFlightFence[i]) != VK_SUCCESS) {
            throw std::runtime_error("14 min");
        }
    }
}

void Pipeline::swapChainRecreation()
{
    //handling minimization (waiting for the window to be reopened)
    int width;
    int height;
    GLFWwindow *window = mainWindow.getWindow();
    glfwGetFramebufferSize(window, &width, &height);

    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(this->device.getDevice());

    //clean up old swapchain

    this->cleanPipeline();
    this->renderPass.~RenderPass();
    this->swapChain.~SwapChain();
    
    
    this->swapChain.recreate(this->physicalDevice, this->instance, static_cast<uint32_t>(mainWindow.getWidth()), static_cast<uint32_t>(mainWindow.getHeight()));
    this->renderPass.recreate(this->swapChain);
    this->createGraphicsPipeline();
    this->initFrameBuffers(this->swapChain);
}

void Pipeline::removeBuffer(Buffer &b)
{
    for (auto it = this->buffers2d.begin(); it != this->buffers2d.end(); ++it) {
        if (&(*it) == &b) {
            this->buffers2d.erase(it);
            return;
        }
    }

    // this->buffers2d.erase(std::find(this->buffers2d.begin(), this->buffers2d.end(), [&](Buffer &node) {
    //     return &node == &b;
    // }));
}

void Pipeline::clearBuffer()
{
    this->buffers2d.clear();
}

}