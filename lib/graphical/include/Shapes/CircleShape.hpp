#ifndef GR_CIRCLE_SHAPE_HPP_
#define GR_CIRCLE_SHAPE_HPP_

#include "ShapeBase.hpp"

namespace gr {
    class CircleShape : public ShapeBase
    {
        public:
            CircleShape(const glm::vec2 &pos, float radius, size_t quality = 0);
    };
}

#endif