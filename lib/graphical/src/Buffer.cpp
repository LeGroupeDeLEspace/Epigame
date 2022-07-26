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

    if (this->indexed) {
        vkDestroyBuffer(this->device.getDevice(), this->ibuffer, nullptr);
        vkFreeMemory(this->device.getDevice(), this->imemory, nullptr);
    }
}

Buffer::Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex, size_t nindex) : device(device)
{
    this->initBuffer(nvertex);
    this->initMemory(physicalDevice);

    vkBindBufferMemory(this->device.getDevice(), this->vbuffer, this->memory, 0);

    this->indexed = false;
    if (nindex > 0) {
        this->nindex = nindex;
        this->indexed = true;

        this->ibuffer = createBuffer(sizeof(uint16_t) * nindex, VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
        this->imemory = createMemory(this->ibuffer, physicalDevice);

        vkBindBufferMemory(this->device.getDevice(), this->ibuffer, this->imemory, 0);
    }
}

Buffer::Buffer(Buffer &&r) : device(r.device)
{
    this->length = r.length;
    this->memory = r.memory;
    this->vbuffer = r.vbuffer;
    this->indexed = r.indexed;
    this->nindex = r.nindex;
    this->imemory = r.imemory;
    this->ibuffer = r.ibuffer;

    r.memory = VK_NULL_HANDLE;
    r.vbuffer = VK_NULL_HANDLE;
    r.ibuffer = VK_NULL_HANDLE;
    r.imemory = VK_NULL_HANDLE;
    r.length = 0;
    r.indexed = false;
}

Buffer& Buffer::operator=(Buffer &&r)
{
    this->length = r.length;
    this->memory = r.memory;
    this->vbuffer = r.vbuffer;
    this->indexed = r.indexed;
    this->nindex = r.nindex;
    this->imemory = r.imemory;
    this->ibuffer = r.ibuffer;

    r.memory = VK_NULL_HANDLE;
    r.vbuffer = VK_NULL_HANDLE;
    r.length = 0;
    r.indexed = false;
    return *this;
}

VkBuffer Buffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage)
{
    VkBuffer buffer;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(this->device.getDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer");
    }
    return buffer;
}

VkDeviceMemory Buffer::createMemory(VkBuffer buffer, const PhysicalDevice &physicalDevice)
{
    VkDeviceMemory memory;
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

    if (vkAllocateMemory(this->device.getDevice(), &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }
    return memory;
}

void Buffer::initBuffer(size_t length)
{
    this->length = length;

    this->vbuffer = createBuffer(sizeof(Vertex) * length, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
}

void Buffer::initMemory(const PhysicalDevice &physicalDevice)
{
    this->memory = this->createMemory(this->vbuffer, physicalDevice);
}

void Buffer::copyData(const Vertex *data)
{
    void *mapped;
    
    vkMapMemory(this->device.getDevice(), this->memory, 0, this->length * sizeof(Vertex), 0, &mapped);
    memcpy(mapped, data, sizeof(Vertex) * this->length);
    vkUnmapMemory(this->device.getDevice(), this->memory);
}

void Buffer::copyIndexData(const uint16_t *data)
{
    void *mapped;

    if (this->indexed == false) {
        throw std::runtime_error("this buffer is not indexed");
    }
    
    vkMapMemory(this->device.getDevice(), this->imemory, 0, this->nindex * sizeof(uint16_t), 0, &mapped);
    memcpy(mapped, data, sizeof(uint16_t) * this->nindex);
    vkUnmapMemory(this->device.getDevice(), this->imemory);
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

void Buffer::draw(VkCommandBuffer commandBuffer) const
{
    VkDeviceSize offsets[] = {0};

    VkBuffer vertexBuffers[] = {this->vbuffer};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    if (indexed) {
        vkCmdBindIndexBuffer(commandBuffer, this->ibuffer, 0, VK_INDEX_TYPE_UINT16);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(this->nindex), 1, 0, 0, 0);
    }
    else {
        vkCmdDraw(commandBuffer, this->length, 1, 0, 0);
    }
}

}