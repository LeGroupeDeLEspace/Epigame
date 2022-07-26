#include "Shapes/RectangleShape.hpp"

namespace gr {

RectangleShape::RectangleShape(const glm::vec2 &pos, const glm::vec2 &size)
{
    this->geometry.resize(4);
    this->indices = {0, 1, 2, 3, 0, 2};

    glm::vec2 currentPos = pos;

    this->geometry.at(0) = {currentPos, {1.0f, 1.0f, 1.0f}};
    currentPos.x += size.x;
    this->geometry.at(1) = {currentPos, {1.0f, 1.0f, 1.0f}};
    currentPos.y += size.y;
    this->geometry.at(2) = {currentPos, {1.0f, 1.0f, 1.0f}};
    currentPos.x -= size.x;
    this->geometry.at(3) = {currentPos, {1.0f, 1.0f, 1.0f}};
}

}