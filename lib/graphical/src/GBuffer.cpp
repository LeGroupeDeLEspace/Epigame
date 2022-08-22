#include <stdexcept>
#include <cstring>
#include "GBuffer.hpp"

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

GBuffer::GBuffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t length) : device(device)
{
    this->initBuffer(length);
    this->initMemory(physicalDevice);

    vkBindBufferMemory(this->device.getDevice(), this->buffer, this->memory, 0);
}

GBuffer::GBuffer(GBuffer &&r) : device(r.device)
{
    this->length = r.length;
    this->buffer = r.buffer;
    this->memory = r.memory;

    r.memory = VK_NULL_HANDLE;
    r.buffer = VK_NULL_HANDLE;
    r.length = 0;
}

GBuffer& GBuffer::operator=(GBuffer &&r)
{
    this->length = r.length;
    this->buffer = r.buffer;
    this->memory = r.memory;

    r.memory = VK_NULL_HANDLE;
    r.buffer = VK_NULL_HANDLE;
    r.length = 0;
    return *this;
}

GBuffer::~GBuffer()
{
    vkDestroyBuffer(this->device.getDevice(), this->buffer, nullptr);
    vkFreeMemory(this->device.getDevice(), this->memory, nullptr);
}

void GBuffer::copyData(const void *data)
{
    void *mapped;
    
    vkMapMemory(this->device.getDevice(), this->memory, 0, this->length, 0, &mapped);
    memcpy(mapped, data, this->length);
    vkUnmapMemory(this->device.getDevice(), this->memory);
}

size_t GBuffer::getSize() const
{
    return this->length;
}

VkBuffer GBuffer::getBuffer() const
{
    return this->buffer;
}

VkDeviceMemory GBuffer::getMemory() const
{
    return this->memory;
}

void GBuffer::initBuffer(size_t length)
{

}

void GBuffer::initMemory(const PhysicalDevice &physicalDevice)
{

}

VkBuffer GBuffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage)
{

}

VkDeviceMemory GBuffer::createMemory(VkBuffer buffer, const PhysicalDevice &physicalDevice)
{

}

}