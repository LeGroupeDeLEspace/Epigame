#ifndef GR_UNIFORM_3D_HPP_
#define GR_UNIFORM_3D_HPP_

#include <glm/glm.hpp>

namespace gr {
    struct Uniform3d {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
}

#endif