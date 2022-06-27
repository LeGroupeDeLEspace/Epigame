#ifndef GR_GRAPHICS_HPP_
#define GR_GRAHPICS_HPP_

#include "WindowHandler.hpp"
#include "VulkanInstance.hpp"
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"

namespace gr {
    class Graphics {
        public:
            Graphics();
            ~Graphics();

            GLFWwindow *getWindow();
        private:
            WindowHandler windowHandler;
            VulkanInstance instance;
            PhysicalDevice physicalDevice;
            LogicalDevice device;
    };
}

#endif