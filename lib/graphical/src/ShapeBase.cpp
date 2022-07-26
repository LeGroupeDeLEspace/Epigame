#include <stdexcept>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Shapes/ShapeBase.hpp"

namespace gr {

ShapeBase::ShapeBase()
{
}

void ShapeBase::transform(const glm::tmat3x3<float> &transform)
{
    for (auto &it : this->geometry) {
        glm::vec3 t = {it.pos.x, it.pos.y, 0};
        t = transform * t;
        it.pos = {t.x, t.y};
        std::cout << glm::to_string(it.pos) << std::endl;
    }
}

const std::vector<Vertex> &ShapeBase::getVertices() const
{
    return this->geometry;
}

const std::vector<uint16_t> &ShapeBase::getIndices() const
{
    return this->indices;
}

size_t ShapeBase::getVertexCount() const
{
    return this->geometry.size();
}

size_t ShapeBase::getIndicesCount() const
{
    return this->indices.size();
}

}