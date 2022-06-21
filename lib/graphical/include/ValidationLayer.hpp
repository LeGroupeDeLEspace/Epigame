#ifndef GR_VALIDATION_LAYER_HPP_
#define GR_VALIDATION_LAYER_HPP_

#include <vulkan/vulkan.hpp>

namespace gr {
    class ValidationLayer {
        public:
            static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    };
}

#endif