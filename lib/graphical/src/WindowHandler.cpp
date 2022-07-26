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

size_t WindowHandler::getWidth() const {
    return this->windowWidth;
}

size_t WindowHandler::getHeight() const {
    return this->windowHeight;
}

WindowHandler mainWindow;

}