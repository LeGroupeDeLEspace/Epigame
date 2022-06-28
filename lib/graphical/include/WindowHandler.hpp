#ifndef GR_WINDOW_HANDLER_HPP_
#define GR_WINDOW_HANDLER_HPP_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace gr {

    class WindowHandler {
        public:
            //WindowHandler(size_t width, size_t height, const std::string &winName);  //TODO
            WindowHandler();
            ~WindowHandler();
        
            GLFWwindow * getWindow();
            size_t getWidth() const;
            size_t getHeight() const;

            //void resize(size_t width, size_t height);
        private:
            GLFWwindow *windowptr;
            size_t windowWidth;
            size_t windowHeight;
    };

}
#endif