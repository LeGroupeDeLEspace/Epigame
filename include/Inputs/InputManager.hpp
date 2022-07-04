#ifndef JEUDELESPACE_INPUTMANAGER_HPP
#define JEUDELESPACE_INPUTMANAGER_HPP

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <map>
#include "GLFW/glfw3.h"
#include "Utils/Command.hpp"
#include "InputEnums.hpp"
#include "Utils/DataContainer.hpp"
#include "Inputs/InputEvent.hpp"

struct InputEventAction {
    DataContainer& container;
    const Axis axis;
    const bool positive;
    int getSignInt();
    float getSignFloat();
    InputEventAction(DataContainer& container, Axis props, bool positive);
};

class InputManager {
private:
    bool cursorInsideApplicationWindows;
    glm::vec2 mousePosition;
    glm::vec2 scrolling;
    std::vector<Joystick> joystickConnected;

    // Events
    std::map<KeyCode, std::vector<InputAction>> keyboardEvents;
    std::map<MouseAxisEvent, std::vector<InputAction>> mouseAxisEvents;
    std::map<MouseButton, std::vector<InputAction>> mouseButtonEvents;

    std::map<GamepadButton, std::vector<InputAction>> gamepadButtonsEvents;
    std::map<GamepadAxis, std::vector<InputAction>> gamepadAxisEvents;

    std::map<InputAction, InputEventAction> inputEvents;
    std::map<InputEvent, DataContainer> events;

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

    InputManager();
public:

    InputManager(const InputManager & copy) = delete;
    InputManager& operator=(const InputManager & copy) = delete;

    ~InputManager();
    static InputManager& instance()
    {
        static auto *instance = new InputManager();
        return *instance;
    }

    void update();
    // The functions for the rest of the
    void loadInputs(std::map<int, std::vector<InputEvent>> inputs); //TODO: change the load
    void changeInput(int oldInput, int newInput, InputEvent event); //TODO: change the changing
    void addAction(InputEvent event, Command1<DataContainer *> * action); // Only adding one at a time for simplicity first.
    void removeAction(InputEvent event, Command1<DataContainer *> * action); // Only removing one at a time for simplicity first.
};

#endif //JEUDELESPACE_INPUTMANAGER_HPP
