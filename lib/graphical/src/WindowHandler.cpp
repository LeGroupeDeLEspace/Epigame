#include "WindowHandler.hpp"

namespace gr {

WindowHandler::WindowHandler() :
windowHeight(800),
windowWidth(600),
windowptr(nullptr)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->windowptr = glfwCreateWindow(this->windowHeight, this->windowWidth, "graph", nullptr, nullptr);
}

WindowHandler::~WindowHandler() {
    glfwDestroyWindow(this->windowptr);
    glfwTerminate();
}

GLFWwindow *WindowHandler::getWindow() {
    return this->windowptr;
}

}