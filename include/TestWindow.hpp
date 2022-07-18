//
// Created by Iannis on 20/06/2022.
//

#ifndef JEUDELESPACE_TESTWINDOW_HPP
#define JEUDELESPACE_TESTWINDOW_HPP

#define WIDTH 1280
#define HEIGHT 720

#include "GLFW/glfw3.h"
class TestWindow{
public:
    static TestWindow& instance()
    {
        static auto *instance = new TestWindow();
        return *instance;
    }
    static GLFWwindow* getCurrentWindow();
    bool update();
private:
    TestWindow();
    GLFWwindow* window;
};

#endif //JEUDELESPACE_TESTWINDOW_HPP
