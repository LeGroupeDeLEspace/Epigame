#ifndef GR_SHAPE_BASE_HPP_
#define GR_SHAPE_BASE_HPP_

#include <cstddef>
#include <glm/glm.hpp>

namespace gr {
    class ShapeBase
    {
        public:
            ShapeBase();

            void transform(const glm::tmat4x4<float> &transform);
        protected:
            size_t vertexCount;
            size_t indiceCount;
    };
}

#endif