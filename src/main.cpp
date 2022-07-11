#include "Graphics.hpp"

int main()
{
    gr::Graphics graph;
    GLFWwindow *window = graph.getWindow();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        graph.test();
    }
    graph.waitForIdle();
    return 0;
}