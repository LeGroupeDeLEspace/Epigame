#ifndef GRAPH_RENDER_HPP_
#define GRAPH_RENDER_HPP_

#include <GLFW/glfw3.h>

class GraphicalInterface {
    public:
        GraphicalInterface();
        ~GraphicalInterface();
        void test();

    private:
        GLFWwindow *window;
};

#endif