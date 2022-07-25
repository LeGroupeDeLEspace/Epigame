#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Buffer.hpp"
#include "Vertex.hpp"

static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, const gr::PhysicalDevice &physicalDevice)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice.getDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if (typeFilter & (1 << i) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties    
        ) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

namespace gr {

Buffer::~Buffer()
{
    vkDestroyBuffer(this->device.getDevice(), this->vbuffer, nullptr);
    vkFreeMemory(this->device.getDevice(), this->memory, nullptr);
}

Buffer::Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex) : device(device)
{
    this->initBuffer(nvertex);
    this->initMemory(physicalDevice);

    vkBindBufferMemory(this->device.getDevice(), this->vbuffer, this->memory, 0);

    std::cout << "Buffer construction: " << nvertex << std::endl;
}

Buffer::Buffer(Buffer &&r) : device(r.device)
{
    this->length = r.length;
    this->memory = r.memory;
    this->vbuffer = r.vbuffer;

    r.memory = VK_NULL_HANDLE;
    r.vbuffer = VK_NULL_HANDLE;
    r.length = 0;
}

void Buffer::initBuffer(size_t length)
{
    this->length = length;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(Vertex) * length;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(this->device.getDevice(), &bufferInfo, nullptr, &this->vbuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer");
    }
}

void Buffer::initMemory(const PhysicalDevice &physicalDevice)
{
    VkMemoryRequirements memRequirements{};
    vkGetBufferMemoryRequirements(this->device.getDevice(), this->vbuffer, &memRequirements);
    
    VkMemoryAllocateInfo allocInfo{};

    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex =
        findMemoryType(memRequirements.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        physicalDevice);

    if (vkAllocateMemory(this->device.getDevice(), &allocInfo, nullptr, &this->memory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }
}

void Buffer::copyData(const Vertex *data)
{
    void *mapped;
    
    vkMapMemory(this->device.getDevice(), this->memory, 0, this->length * sizeof(Vertex), 0, &mapped);
    memcpy(mapped, data, sizeof(Vertex) * this->length);
    vkUnmapMemory(this->device.getDevice(), this->memory);
}

VkBuffer Buffer::getBuffer() const
{
    return this->vbuffer;
}

VkDeviceMemory Buffer::getMemory() const
{
    return this->memory;
}

size_t Buffer::getVCount() const
{
    return this->length;
}

}