#ifndef JEUDELESPACE_INPUTS_HPP
#define JEUDELESPACE_INPUTS_HPP

#include "Command.hpp"
#include "GLFW/glfw3.h"
#include "InputEnums.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>

class Inputs {
private:
    bool cursorInsideApplicationWindows;
    glm::dvec2 mousePosition;
    glm::dvec2 scrolling;
    std::vector<Joystick> joystickConnected;

    // Events
    std::unordered_map<KeyCode, std::vector<std::string>> keyboardEvent;
    std::unordered_map<std::string, Command0*> eventAction;

    static void keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods);
    void keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods);

    static void cursorPositionCallbackStatic(GLFWwindow* window, double xpos, double ypos);
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    static void mouseButtonCallbackStatic(GLFWwindow* window, MouseButton button, InputState action, InputModifier mods);
    void mouseButtonCallback(GLFWwindow* window, MouseButton button, InputState action, InputModifier mods);

    static void scrollCallbackStatic(GLFWwindow* window, double xoffset, double yoffset);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static void mouseEnterWindowCallbackStatic(GLFWwindow* window, int entered);
    void mouseEnterWindowCallback(GLFWwindow* window, int entered);

    static void joystickCallbackStatic(Joystick joystickId, int event);
    void joystickCallback(Joystick joystickId, int event);



    Inputs();
public:
    ~Inputs();
    static Inputs& instance()
    {
        static auto *instance = new Inputs();
        return *instance;
    }

    void update();
    // The functions for the rest of the
    void loadInputs(std::unordered_map<int, std::vector<std::string>> inputs);
    void changeInput(int oldInput, int newInput, std::string event);
    void addAction(std::string event, Command0& action);
    void addAction(std::string event, std::vector<Command0> actions);
    void removeAction(std::string event, Command0& action);
    void removeAction(std::string event, std::vector<Command0&> actions);
};
#endif //JEUDELESPACE_INPUTS_HPP
