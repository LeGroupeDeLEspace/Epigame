#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <map>
#include "Inputs/InputEvent.hpp"
#include "Inputs/InputManager.hpp"
#include "TestWindow.hpp"

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

InputEventAction::InputEventAction(DataContainer& container, Axis props, bool positive): container(container), axis(props), positive(positive){}
int InputEventAction::getSignInt() {return positive ? 1 : -1;}
float InputEventAction::getSignFloat() {return positive ? 1 : -1;}

InputManager::InputManager() :
        joystickConnected(),
        keyboardEvents(),

        events({
       {InputEvent::Move, DataContainer(DataType::Vec3)},
       {InputEvent::Look, DataContainer(DataType::Vec2)},
    }),

        inputEvents({
        //Move Events
        {InputAction::MoveForward, InputEventAction(events.at(InputEvent::Move), Axis::Z, true)},
        {InputAction::MoveBackward, InputEventAction(events.at(InputEvent::Move), Axis::Z, false)},
        {InputAction::MoveRight, InputEventAction(events.at(InputEvent::Move), Axis::X, true)},
        {InputAction::MoveLeft, InputEventAction(events.at(InputEvent::Move), Axis::X, false)},
        {InputAction::MoveUp, InputEventAction(events.at(InputEvent::Move), Axis::Y, true)},
        {InputAction::MoveDown, InputEventAction(events.at(InputEvent::Move), Axis::Y, false)},

        //Look Event
        {InputAction::LookUp, InputEventAction(events.at(InputEvent::Look), Axis::Y, true)},
        {InputAction::LookDown, InputEventAction(events.at(InputEvent::Look), Axis::Y, false)},
        {InputAction::LookRight, InputEventAction(events.at(InputEvent::Look), Axis::X, true)},
        {InputAction::LookLeft, InputEventAction(events.at(InputEvent::Look), Axis::X, false)},
    })
{
    //Get the windows
    GLFWwindow* window = TestWindow::getCurrentWindow();

    // Initializing the keyboards inputs
    std::cout << "Initializing the keyboard inputs" << std::endl;
    glfwSetKeyCallback(window, (GLFWkeyfun)(InputManager::keyCallbackStatic));

    // Initializing the mouse buttons
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)InputManager::mouseButtonCallbackStatic);

    // Initializing the mouse position
    std::cout << "Initializing the mouse positions" << std::endl;
    glfwSetCursorPosCallback(window, InputManager::cursorPositionCallbackStatic);

    // Initializing the scrolling
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetScrollCallback(window, InputManager::scrollCallbackStatic);

    // Initializing the mouse focus
    std::cout << "Initializing the mouse focus" << std::endl;
    glfwSetCursorEnterCallback(window, InputManager::mouseEnterWindowCallbackStatic);

    glfwSetJoystickCallback((GLFWjoystickfun)InputManager::joystickCallbackStatic);
}

InputManager::~InputManager() {

}

void InputManager::keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void InputManager::keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    // Don't want to use the repeat action
    if(action == InputState::Repeat) return;

    if (keyboardEvents.contains(key)) {
        for (auto & event : keyboardEvents.at(key)) {
            LOG("Updating the event " << InputActionName[event]);

            auto & input = inputEvents.at(event);
            auto containerType = input.container.type;

            if (containerType == DataType::Bool) {
                LOG("We update a boolean value");
                input.container.setData(action == InputState::Press);
            }
            else if (containerType % 2 == 0) { // Setting a float
                LOG("We update a float value");
                float final = input.container.getFloat(input.axis) + (action == InputState::Press ? input.getSignFloat() : -input.getSignFloat());
                input.container.setValue(final, input.axis);
            }
            else { // is implicitly "containerType % 2 == 0" => setting an int
                LOG("We update a int value");
                int final = input.container.getInt(input.axis) + (action == InputState::Press ? input.getSignInt() : - input.getSignInt());
                input.container.setValue(final, input.axis);
            }
        }
    }
}

void InputManager::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {
    InputManager::instance().cursorPositionCallback(window, xpos, ypos);
}

void InputManager::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    auto previousMousePosition = this->mousePosition;
    this->mousePosition = glm::vec2 {xpos, ypos};

    if (this->mouseAxisEvents.contains(MouseAxisEvent::Position)) {
        for (auto & inputAction : this->mouseAxisEvents[MouseAxisEvent::Position]) {
            inputEvents.at(inputAction).container.setData(this->mousePosition);
        }
    }

    if (this->mouseAxisEvents.contains(MouseAxisEvent::DeltaMovement)) {
        for (auto & inputAction : this->mouseAxisEvents[MouseAxisEvent::DeltaMovement]) {
            inputEvents.at(inputAction).container.setData(this->mousePosition - previousMousePosition);
        }
    }
}

void InputManager::mouseButtonCallbackStatic(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    InputManager::instance().mouseButtonCallback(window, button, action, mods);
}

void InputManager::mouseButtonCallback(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    // Don't want to use the repeat action
    if(action == InputState::Repeat) return;

    if (this->mouseButtonEvents.contains(button)) {
        for (auto & inputAction : this->mouseButtonEvents[button]) {
            auto & event = inputEvents.at(inputAction);
            switch (event.axis) {
                case None:
                    event.container.setData(action == InputState::Press);
                    break;
                default:
                    event.container.setData(action == InputState::Press ? 1.0f : 0.0f);
                    break;
            }
        }
    }
}

void InputManager::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {
    InputManager::instance().scrollCallback(window, xoffset, yoffset);
}

void InputManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scrolling = glm::vec2 {xoffset, yoffset};

    if (this->mouseAxisEvents.contains(MouseAxisEvent::DeltaScroll)) {
        for (auto & inputAction : this->mouseAxisEvents[MouseAxisEvent::DeltaScroll]) {
            inputEvents.at(inputAction).container.setData(this->scrolling);
        }
    }
}

void InputManager::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {
    InputManager::instance().mouseEnterWindowCallback(window, entered);
}

void InputManager::mouseEnterWindowCallback(GLFWwindow *window, int entered) {
    this->cursorInsideApplicationWindows = entered;
    if (entered) {
        LOG("The cursor is inside the application window.");
    } else {
        LOG("The cursor is outside the application window.");
    }
}

void InputManager::joystickCallbackStatic(Joystick joystickId, int event) {
    InputManager::instance().joystickCallback(joystickId, event);
}

void InputManager::joystickCallback(Joystick jid, int event) {
    const char* joystickName = glfwGetJoystickName((int)jid);
    std::string name;
    if (joystickName != nullptr) {
        name = std::string {joystickName};
    } else {
        name = &"Joystick_"[(int)jid];
    }
    if (event == GLFW_CONNECTED)
    {
        // The joystick was connected
        this->joystickConnected.push_back(jid);
        LOG(name << " has been connected.");
        LOG("There is now " << joystickConnected.size() << " joystick connected.");
    }
    else if (event == GLFW_DISCONNECTED)
    {
        // The joystick was disconnected
        LOG(name << " has been disconnected.");
        auto index = std::find(this->joystickConnected.begin(), this->joystickConnected.end(),jid);
        if (index != this->joystickConnected.end()) {
            this->joystickConnected.erase(index);
            LOG("There is now " << joystickConnected.size() << " joystick connected.");
        } else {
            LOG("The joystick " << name << " hasn't been connected");
        }
    }
}

// Updating the joystick
void InputManager::update() {
//    LOG("There is " << this->joystickConnected.size() << "Joystick connected.");
    for (auto & joystick : this->joystickConnected) {
        int jid = (int)joystick;

        // Logging the different axis
        int axisCount;
        const float* axes = glfwGetJoystickAxes(jid, &axisCount);
        for (int i = 0; i < axisCount; ++i) {
            auto axis = (GamepadAxis)i;
            if (gamepadAxisEvents.contains(axis)) {
                for (auto & inputAction : gamepadAxisEvents[axis]) {
                    auto & e = inputEvents.at(inputAction);
                    e.container.setValue(axes[i] * e.getSignFloat(), e.axis);
                }
            }
        }

        // Logging the different buttons
        int buttonCount;
        const unsigned char* buttons = glfwGetJoystickButtons(jid, &buttonCount);
        for (int i = 0; i < buttonCount; ++i) {
            auto button = (GamepadButton)i;
            if (gamepadButtonsEvents.contains(button)) {
                for (auto & inputAction : gamepadButtonsEvents[button]) {
                    auto & e = inputEvents.at(inputAction);
                    switch (e.axis) {
                        case None:
                            e.container.setData((buttons[i] == 1) == e.positive);
                            break;
                        default:
                            e.container.setValue(buttons[i] * e.getSignInt(),e.axis);
                            break;
                    }
                }
            }
        }
    }
}
