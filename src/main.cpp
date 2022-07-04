#include <System.hpp>
#include <iostream>
#include "Graphics.hpp"

int main()
{
    std::cout << su::System::resolvePath(std::vector<std::string> {
        "a", "b"
    }) << std::endl;
    gr::Graphics graph;
    GLFWwindow *window = graph.getWindow();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    return 0;
}