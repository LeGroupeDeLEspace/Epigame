#include "TestWindow.hpp"
#include "Inputs/InputsManager.hpp"
#include "iostream"
int main()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow testWindow = TestWindow::instance();
    InputsManager input = InputsManager::instance();
    do {
        result = testWindow.update();
        input.update();
    } while (result);
}
