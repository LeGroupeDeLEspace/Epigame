#ifndef GR_QUEUE_FAMILY_INDICES
#define GR_QUEUE_FAMILY_INDICES

#include <vulkan/vulkan.h>
#include <optional>

namespace gr {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete();
    };
}

#endif