#include "TestWindow.hpp"
#include "Inputs/Inputs.hpp"
#include "iostream"
int main()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow testWindow = TestWindow::instance();
    Inputs input = Inputs::instance();
    do {
        result = testWindow.update();
        input.update();
    } while (result);
}
