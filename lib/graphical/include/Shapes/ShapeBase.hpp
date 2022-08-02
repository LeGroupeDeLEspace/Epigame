#ifndef GR_SHAPE_BASE_HPP_
#define GR_SHAPE_BASE_HPP_

#include <cstddef>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.hpp"

namespace gr {
    class ShapeBase
    {
        public:
            ShapeBase();

            void transform(const glm::tmat3x3<float> &transform);
            void setColor(const glm::vec3 &color);

            const std::vector<Vertex> &getVertices() const;
            const std::vector<uint16_t> &getIndices() const;
            size_t getVertexCount() const;
            size_t getIndicesCount() const;
        protected:
            std::vector<Vertex> geometry;
            std::vector<uint16_t> indices;
    };
}

#endif