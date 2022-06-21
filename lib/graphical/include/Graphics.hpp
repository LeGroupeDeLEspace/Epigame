#ifndef GR_GRAPHICS_HPP_
#define GR_GRAHPICS_HPP_

#include "WindowHandler.hpp"
#include "VulkanInstance.hpp"

namespace gr {
    class Graphics {
        public:
            Graphics();
            ~Graphics();

            GLFWwindow *getWindow();
        private:
            void free();
            GLFWwindow *window;
            VulkanInstance *instance;
    };
}

#endif