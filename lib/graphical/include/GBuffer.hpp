#ifndef GR_GBUFFER_HPP_
#define GR_GBUFFER_HPP_

#include "LogicalDevice.hpp"

// code duplicated from the Vertex Buffer (Buffer.hpp).
// Vertex Buffer should inherite or uses this class
namespace gr {
    class GBuffer {
        public:
            GBuffer(const LogicalDevice &device, const PhysicalDevice &physicalDevice, size_t length);
            GBuffer(GBuffer &&r);
            GBuffer& operator=(GBuffer &&r);

            ~GBuffer();

            void copyData(const void *data);

            size_t getSize() const;
            VkBuffer getBuffer() const;
            VkDeviceMemory getMemory() const;

        private:

            void initBuffer(size_t length);

            void initMemory(const PhysicalDevice &physicalDevice);

            VkBuffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage);
            VkDeviceMemory createMemory(VkBuffer buffer, const PhysicalDevice &physicalDevice);

            const LogicalDevice &device;
            size_t length;
            VkDeviceMemory memory;
            VkBuffer buffer;
    };
}

#endif