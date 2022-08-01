#ifndef GR_SHAPES_MANAGER_HPP_
#define GR_SHAPES_MANAGER_HPP_

#include "Pipeline.hpp"
#include "Shapes/ShapeBase.hpp"

namespace gr {
    class ShapesManager {
        public:
            ShapesManager(Pipeline &pipeline);

            void loadShapes(const std::vector<ShapeBase*> &shapes);
            void clear();
            void copyDataToBuffer();

            bool autoUpdate;
        private:
            void createBuffer();

            struct ShapeRef {
                ShapeBase* shape;
                size_t vertex_offset;
                size_t indice_offset;
            };

            Pipeline &pipeline;
            Buffer *buffer;
            std::vector<ShapeRef> shapes;
            size_t totalVertices;
            size_t totalIndices;
    };
}

#endif