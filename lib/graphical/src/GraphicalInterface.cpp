#include <iostream>
#include <GLFW/glfw3.h>
#include "graphRender.hpp"

const int WIDTH = 600;
const int HEIGHT = 500;

GraphicalInterface::GraphicalInterface() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);
}

GraphicalInterface::~GraphicalInterface() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void GraphicalInterface::test()
{
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}