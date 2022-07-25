#ifndef GR_SHAPES_MANAGER_HPP_
#define GR_SHAPES_MANAGER_HPP_

#include "Pipeline.hpp"
#include "Shapes/ShapeBase.hpp"

namespace gr {
    class ShapesManager {
        public:
            ShapesManager(Pipeline &pipeline);

            void loadShapes(std::vector<ShapeBase*> shapes);
            void clear();
        private:
            Pipeline &pipeline;
    };
}

#endif