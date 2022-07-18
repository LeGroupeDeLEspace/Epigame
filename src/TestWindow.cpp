//
// Created by Iannis on 20/06/2022.
//

#include "TestWindow.hpp"

TestWindow::TestWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);
}

bool TestWindow::update() {
    if (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
        return true;
    }
    return false;
}

GLFWwindow *TestWindow::getCurrentWindow() {
    return instance().window;
}
