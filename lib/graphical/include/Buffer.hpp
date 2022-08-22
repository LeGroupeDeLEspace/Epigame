#ifndef GR_VERTEX_BUFFER_HPP_
#define GR_VERTEX_BUFFER_HPP_

#include "LogicalDevice.hpp"
#include "Vertex.hpp"

namespace gr {
    class Buffer {
        public:
            Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex, size_t nindex = 0);
            // Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex, VkMemoryPropertyFlags properties); // TODO implement this

            Buffer(const Buffer &r) = delete;

            Buffer(Buffer &&r);

            Buffer& operator=(Buffer &&r);

            ~Buffer();

            void copyData(const Vertex *data);
            void copyIndexData(const uint16_t *data);

            size_t getVCount() const;
            VkBuffer getBuffer() const;
            VkDeviceMemory getMemory() const;

            void draw(VkCommandBuffer commandBuffer) const;
        private:

            void initBuffer(size_t length);

            void initMemory(const PhysicalDevice &physicalDevice);

            VkBuffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage);
            VkDeviceMemory createMemory(VkBuffer buffer, const PhysicalDevice &physicalDevice);

            const LogicalDevice &device;

            bool indexed;
            size_t nindex;

            size_t length;
            VkDeviceMemory memory;
            VkBuffer vbuffer;

            VkDeviceMemory imemory;
            VkBuffer ibuffer;
    };
}

#endif