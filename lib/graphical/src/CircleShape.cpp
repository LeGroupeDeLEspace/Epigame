#include <cmath>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "Shapes/CircleShape.hpp"

namespace gr {

CircleShape::CircleShape(const glm::vec2 &pos, float radius, size_t quality)
{
    const size_t divisions = 3 + quality;
    this->geometry.resize(1 + divisions);
    this->geometry[0] = {pos, {1.0f, 1.0f, 1.0f}};
    
    for (size_t i = 0; i < divisions; i++) {
        float angle = ((float) i / (float) divisions) * 2 * M_PI;
        this->geometry[i + 1] = {{pos.x + std::cos(angle) * radius, pos.y + std::sin(angle) * radius}, {1.0f, 1.0f, 1.0f}};
        this->indices.push_back(i + 1);
        if (i == (divisions - 1))
            this->indices.push_back(1);
        else
            this->indices.push_back(i+2);
        this->indices.push_back(0);
    }
}

}