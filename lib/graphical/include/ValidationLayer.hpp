#ifndef GR_VALIDATION_LAYER_HPP_
#define GR_VALIDATION_LAYER_HPP_

#include <vulkan/vulkan.hpp>

namespace gr {
    class ValidationLayer {
        public:
            ValidationLayer(VkInstance instance);
            ~ValidationLayer();
            static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        private:

            VkResult CreateDebugUtilsMessengerEXT(
                VkInstance instance,
                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                const VkAllocationCallbacks* pAllocator,
                VkDebugUtilsMessengerEXT * pDebugMessenger);
            void DestroyDebugUtilsMessengerEXT(
                VkInstance instance,
                VkDebugUtilsMessengerEXT debugMessenger,
                const VkAllocationCallbacks* pAllocator);

            const VkInstance instance;
            VkDebugUtilsMessengerEXT messenger;
    };
}

#endif