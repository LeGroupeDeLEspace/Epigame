#ifndef GR_LOGICAL_DEVICE_HPP_
#define GR_LOGICAL_DEVICE_HPP_

#include "PhysicalDevice.hpp"

namespace gr {

    class LogicalDevice {
        public:
            LogicalDevice(const PhysicalDevice &physicalDevice);
            ~LogicalDevice();
        private:
            VkDevice device;

            VkQueue graphicsQueue;
            VkQueue presentQueue;
    };

}

#endif