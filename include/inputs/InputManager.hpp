#ifndef JEUDELESPACE_INPUTMANAGER_HPP
#define JEUDELESPACE_INPUTMANAGER_HPP

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <unordered_map>
#include "GLFW/glfw3.h"
#include "utils/Command.hpp"
#include "InputEnums.hpp"
#include "utils/DataContainer.hpp"
#include "inputs/InputEvent.hpp"

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
    std::vector<Joystick::JoystickId> joystickConnected;

    // Events
    std::unordered_map<Keyboard::KeyCode, std::vector<Input::Action>> keyboardEvents;
    std::unordered_map<Mouse::Axis, std::vector<Input::Event>> mouseAxisEvents;
    std::unordered_map<Mouse::Button, std::vector<Input::Action>> mouseButtonEvents;

    std::unordered_map<Gamepad::Button, std::vector<Input::Action>> gamepadButtonsEvents;
    std::unordered_map<Gamepad::Axis, std::vector<Input::Action>> gamepadAxisEvents;

    std::unordered_map<Input::Event, DataContainer> events;
    std::unordered_map<Input::Action, InputEventAction> inputEvents;

    static void keyCallbackStatic(GLFWwindow* window, Keyboard::KeyCode key, int scancode, Input::State action, Input::Modifier mods);
    void keyCallback(GLFWwindow* window, Keyboard::KeyCode key, int scancode, Input::State action, Input::Modifier mods);

    static void cursorPositionCallbackStatic(GLFWwindow* window, double xpos, double ypos);
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    static void mouseButtonCallbackStatic(GLFWwindow* window, Mouse::Button button, Input::State action, Input::Modifier mods);
    void mouseButtonCallback(GLFWwindow* window, Mouse::Button button, Input::State action, Input::Modifier mods);

    static void scrollCallbackStatic(GLFWwindow* window, double xoffset, double yoffset);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static void mouseEnterWindowCallbackStatic(GLFWwindow* window, int entered);
    void mouseEnterWindowCallback(GLFWwindow* window, int entered);

    static void joystickCallbackStatic(Joystick::JoystickId joystickId, int event);
    void joystickCallback(Joystick::JoystickId joystickId, int event);

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
    void loadInputs(std::unordered_map<int, std::vector<Input::Event>> inputs); //TODO: change the load
    void changeInput(int oldInput, int newInput, Input::Event event); //TODO: change the changing
    void addAction(Input::Event event, Command1<DataContainer *> * action); // Only adding one at a time for simplicity first.
    void removeAction(Input::Event event, Command1<DataContainer *> * action); // Only removing one at a time for simplicity first.
    void clearAllEvents(Input::Event event);
};

#endif //JEUDELESPACE_INPUTMANAGER_HPP
