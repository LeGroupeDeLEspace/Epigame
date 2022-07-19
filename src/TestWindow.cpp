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

void TestWindow::update() {
    glfwPollEvents();
}

bool TestWindow::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

GLFWwindow *TestWindow::getCurrentWindow() {
    return instance().window;
}
