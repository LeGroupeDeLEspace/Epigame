#ifndef GR_VERTEX_BUFFER_HPP_
#define GR_VERTEX_BUFFER_HPP_

#include "LogicalDevice.hpp"
#include "Vertex.hpp"

namespace gr {
    class Buffer {
        public:
            Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex);
            Buffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t nvertex, VkMemoryPropertyFlags properties); // TODO implement this

            Buffer(const Buffer &r) = delete;

            Buffer(Buffer &&r);

            ~Buffer();

            void copyData(const Vertex *data); // TODO implement length / offset

            size_t getVCount() const;
            VkBuffer getBuffer() const;
            VkDeviceMemory getMemory() const;
        private:

            void initBuffer(size_t length);

            void initMemory(const PhysicalDevice &physicalDevice);

            const LogicalDevice &device;
            size_t length;
            VkDeviceMemory memory;
            VkBuffer vbuffer;
    };
}

#endif