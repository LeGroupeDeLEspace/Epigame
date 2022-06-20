#include "inputs.hpp"
#include "iostream"
#include "TestWindow.hpp"

Inputs::Inputs(){
    //TODO: find the window !
    GLFWwindow* window = TestWindow::getCurrentWindow();
    std::cout << "Initialize Inputs" << std::endl;
    glfwSetKeyCallback(window, Inputs::keyCallbackStatic);
}

Inputs::~Inputs(){

}

void Inputs::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "window = " << window << std::endl;
    std::cout << "key = " << key << std::endl;
    std::cout << "scancode = " << scancode << std::endl;
    std::cout << "action = " << action << std::endl;
    std::cout << "mods = " << mods << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void Inputs::keyCallbackStatic(GLFWwindow *window, int key, int scancode, int action, int mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}
