#ifndef GR_GRAPHICS_HPP_
#define GR_GRAHPICS_HPP_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace gr {
    class Graphics {
        public:
            Graphics();
            ~Graphics();

            GLFWwindow *getWindow();
        private:
            GLFWwindow *window;
    };
}

#endif