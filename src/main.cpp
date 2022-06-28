#include "Graphics.hpp"

int main()
{
    gr::Graphics graph;
    GLFWwindow *window = graph.getWindow();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    return 0;
}