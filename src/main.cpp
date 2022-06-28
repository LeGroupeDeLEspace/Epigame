#include "TestWindow.hpp"
#include "Inputs/InputManager.hpp"
#include "iostream"
int main()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow testWindow = TestWindow::instance();
    InputManager input = InputManager::instance();
    do {
        result = testWindow.update();
        input.update();
    } while (result);
}
