#ifndef GR_RECTANGLE_SHAPE_HPP_
#define GR_RECTANGLE_SHAPE_HPP_

#include "ShapeBase.hpp"

namespace gr {
    class RectangleShape : public ShapeBase
    {
        public:
            RectangleShape(const glm::vec2 &pos, const glm::vec2 &size);
    };
}

#endif