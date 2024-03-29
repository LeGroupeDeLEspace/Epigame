#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <unordered_map>
#include "inputs/InputEvent.hpp"
#include "inputs/InputManager.hpp"
#include "WindowHandler.hpp"
#include "Graphics.hpp"

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

InputEventAction::InputEventAction(DataContainer& container, Axis props, bool positive): container(container), axis(props), positive(positive){}
int InputEventAction::getSignInt() {return positive ? 1 : -1;}
float InputEventAction::getSignFloat() {return positive ? 1 : -1;}

InputManager::InputManager() :
        joystickConnected(),
        keyboardEvents(),
        mouseAxisEvents(),
        mouseButtonEvents(),
        gamepadButtonsEvents(),
        gamepadAxisEvents(),
        events({
           {Input::Event::Move, DataContainer(DataType::Vec3)},
           {Input::Event::Look, DataContainer(DataType::Vec2)},
           {Input::Event::Jump, DataContainer(DataType::Bool)},
        }),
        inputEvents({
            //Move Events
            {Input::Action::MoveForward,  InputEventAction(this->events.at(Input::Event::Move), Axis::Z, true)},
            {Input::Action::MoveBackward, InputEventAction(this->events.at(Input::Event::Move), Axis::Z, false)},
            {Input::Action::MoveRight,    InputEventAction(this->events.at(Input::Event::Move), Axis::X, true)},
            {Input::Action::MoveLeft,     InputEventAction(this->events.at(Input::Event::Move), Axis::X, false)},
            {Input::Action::MoveUp,       InputEventAction(this->events.at(Input::Event::Move), Axis::Y, true)},
            {Input::Action::MoveDown,     InputEventAction(this->events.at(Input::Event::Move), Axis::Y, false)},

            //Look Event
            {Input::Action::LookUp,       InputEventAction(this->events.at(Input::Event::Look), Axis::Y, true)},
            {Input::Action::LookDown,     InputEventAction(this->events.at(Input::Event::Look), Axis::Y, false)},
            {Input::Action::LookRight,    InputEventAction(this->events.at(Input::Event::Look), Axis::X, true)},
            {Input::Action::LookLeft,     InputEventAction(this->events.at(Input::Event::Look), Axis::X, false)},

            //Jump Event
            {Input::Action::JumpAction,     InputEventAction(this->events.at(Input::Event::Jump), Axis::None, true)},
        })
{
    //Get the windows
    GLFWwindow* window = gr::mainWindow.getWindow();

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
    // Creating some test events
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::W, std::vector<Input::Action>({Input::Action::MoveForward})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::S, std::vector<Input::Action>({Input::Action::MoveBackward})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::A, std::vector<Input::Action>({Input::Action::MoveLeft})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::D, std::vector<Input::Action>({Input::Action::MoveRight})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::Q, std::vector<Input::Action>({Input::Action::MoveUp})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::E, std::vector<Input::Action>({Input::Action::MoveDown})));
    this->keyboardEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Keyboard::KeyCode::Space, std::vector<Input::Action>({Input::Action::JumpAction})));

//    this->mouseAxisEvents.insert(std::make_pair<Keyboard::KeyCode,std::vector<Input::Action>>(Mouse::Axis::DeltaMovement, std::vector<Input::Action>({Input::Action::})));
}

InputManager::~InputManager() {

}

void InputManager::keyCallbackStatic(GLFWwindow* window, Keyboard::KeyCode key, int scancode, Input::State action, Input::Modifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void InputManager::keyCallback(GLFWwindow* window, Keyboard::KeyCode key, int scancode, Input::State action, Input::Modifier mods) {
    // Don't want to use the repeat action
    if(action == Input::State::Repeat) return;

    if (keyboardEvents.contains(key)) {
        for (auto & event : keyboardEvents.at(key)) {
//            LOG("Updating the event " << InputActionName[event]);

            auto & input = inputEvents.at(event);
            auto containerType = input.container.type;

            if (containerType == DataType::Bool) {
//                LOG("We update a boolean value");
                input.container.setData(action == Input::State::Press);
            }
            else if (containerType % 2 == 0) { // Setting a float
//                LOG("We update a float value");
                float final = input.container.getFloat(input.axis) + (action == Input::State::Press ? input.getSignFloat() : -input.getSignFloat());
                input.container.setValue(final, input.axis);
            }
            else { // is implicitly "containerType % 2 == 0" => setting an int
//                LOG("We update a int value");
                int final = input.container.getInt(input.axis) + (action == Input::State::Press ? input.getSignInt() : - input.getSignInt());
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

    if (this->mouseAxisEvents.contains(Mouse::Axis::Position)) {
        for (auto & inputAction : this->mouseAxisEvents[Mouse::Axis::Position]) {
            events.at(inputAction).setData(this->mousePosition);
        }
    }

    if (this->mouseAxisEvents.contains(Mouse::Axis::DeltaMovement)) {
        for (auto & inputAction : this->mouseAxisEvents[Mouse::Axis::DeltaMovement]) {
            events.at(inputAction).setData(this->mousePosition - previousMousePosition);
        }
    }
}

void InputManager::mouseButtonCallbackStatic(GLFWwindow *window, Mouse::Button button, Input::State action, Input::Modifier mods) {
    InputManager::instance().mouseButtonCallback(window, button, action, mods);
}

void InputManager::mouseButtonCallback(GLFWwindow *window, Mouse::Button button, Input::State action, Input::Modifier mods) {
    // Don't want to use the repeat action
    if(action == Input::State::Repeat) return;

    if (this->mouseButtonEvents.contains(button)) {
        for (auto & inputAction : this->mouseButtonEvents[button]) {
            auto & event = inputEvents.at(inputAction);
            switch (event.axis) {
                case None:
                    event.container.setData(action == Input::State::Press);
                    break;
                default:
                    event.container.setData(action == Input::State::Press ? 1.0f : 0.0f);
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

    if (this->mouseAxisEvents.contains(Mouse::Axis::DeltaScroll)) {
        for (auto & inputAction : this->mouseAxisEvents[Mouse::Axis::DeltaScroll]) {
            events.at(inputAction).setData(this->scrolling);
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

void InputManager::joystickCallbackStatic(Joystick::JoystickId joystickId, int event) {
    InputManager::instance().joystickCallback(joystickId, event);
}

void InputManager::joystickCallback(Joystick::JoystickId jid, int event) {
    const char* joystickName = glfwGetJoystickName((int)jid);
    std::string name;
    if (joystickName != nullptr) {
        name = std::string {joystickName};
    } else {
        name = &"Joystick_"[(int)jid];
    }
    if (event == GLFW_CONNECTED)
    {
        if(glfwJoystickIsGamepad(jid))
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
//    LOG("There is " << this->joystickConnected.size() << "JoystickId connected.");
    for (auto & joystick : this->joystickConnected) {

        // Logging the different axis
        int axisCount;
        const float* axes = glfwGetJoystickAxes(joystick, &axisCount);
        for (int i = 0; i < axisCount; ++i) {
            auto axis =  (Gamepad::Axis)i;
            if (gamepadAxisEvents.contains(axis)) {
                for (auto & inputAction : gamepadAxisEvents[axis]) {
                    auto & e = inputEvents.at(inputAction);
                    e.container.setValue(axes[i] * e.getSignFloat(), e.axis);
                }
            }
        }

        // Logging the different buttons
        int buttonCount;
        const unsigned char* buttons = glfwGetJoystickButtons(joystick, &buttonCount);
        for (int i = 0; i < buttonCount; ++i) {
            auto button = (Gamepad::Button)i;
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

void InputManager::addAction(Input::Event event, Command1<DataContainer *> * action) {
    this->events.at(event) += action;
}

void InputManager::removeAction(Input::Event event, Command1<DataContainer *> * action) {
    this->events.at(event) -= action;
}

void InputManager::clearAllEvents(Input::Event event) {
    this->events.at(event).clearAllEvents();
}
