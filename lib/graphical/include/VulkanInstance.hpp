#ifndef GR_VULKAN_INSTANCE_HPP_
#define GR_VULKAN_INSTANCE_HPP_

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vector>
#include "ValidationLayer.hpp"

namespace gr {
    class VulkanInstance {
        public:
            VulkanInstance(GLFWwindow *window);
            ~VulkanInstance();

            static std::vector<const char *> getRequiredExtensions();
            const VkInstance &getInstance() const;
            const VkSurfaceKHR &getSurface() const;
        private:
            void createInstance();
            void createSurface(GLFWwindow *window);

            VkInstance instance;
            ValidationLayer *validationLayer;
            VkSurfaceKHR surface;
    };
}

#endif