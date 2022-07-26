#include <stdexcept>
#include "Shapes/ShapeBase.hpp"

namespace gr {

ShapeBase::ShapeBase()
{
}

void ShapeBase::transform(const glm::tmat4x4<float> &transform)
{
    throw std::runtime_error("not implemented");
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