#ifndef GR_VERTEX_HPP_
#define GR_VERTEX_HPP_

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

namespace gr {

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

}

#endif