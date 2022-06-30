#include "Graphics.hpp"

int main()
{
    gr::Graphics graph;
    GLFWwindow *window = graph.getWindow();
    InputManager input = InputManager::instance();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        input.update();
    }
    return 0;
}
