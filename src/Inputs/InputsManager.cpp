#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include "TestWindow.hpp"
#include "Inputs/InputEvent.hpp"
#include "Inputs/InputsManager.hpp"

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

InputEventAction::InputEventAction(DataContainer& container, DataProps props, bool positive): container(container), props(props), positive(positive) {}

InputsManager::InputsManager() :
    joystickConnected(),
    keyboardEvent(),

    events({
       {InputEvent::Move, DataContainer(DataType::Vec3)},
       {InputEvent::Look, DataContainer(DataType::Vec2)},
    }),

    inputEvents({
        //Move Events
        {InputAction::MoveForward, InputEventAction(events.at(InputEvent::Move),DataProps::Z, true)},
        {InputAction::MoveBackward, InputEventAction(events.at(InputEvent::Move),DataProps::Z, false)},
        {InputAction::MoveRight, InputEventAction(events.at(InputEvent::Move),DataProps::X, true)},
        {InputAction::MoveLeft, InputEventAction(events.at(InputEvent::Move),DataProps::X, false)},
        {InputAction::MoveUp, InputEventAction(events.at(InputEvent::Move),DataProps::Y, true)},
        {InputAction::MoveDown, InputEventAction(events.at(InputEvent::Move),DataProps::Y, false)},

        //Look Event
        {InputAction::LookUp, InputEventAction(events.at(InputEvent::Look),DataProps::Y, true)},
        {InputAction::LookDown, InputEventAction(events.at(InputEvent::Look),DataProps::Y, false)},
        {InputAction::LookRight, InputEventAction(events.at(InputEvent::Look),DataProps::X, true)},
        {InputAction::LookLeft, InputEventAction(events.at(InputEvent::Look),DataProps::X, false)},
    })
{
    //Get the windows
    GLFWwindow* window = TestWindow::getCurrentWindow();

    // Initializing the keyboards inputs
    std::cout << "Initializing the keyboard inputs" << std::endl;
    glfwSetKeyCallback(window, (GLFWkeyfun)(InputsManager::keyCallbackStatic));

    // Initializing the mouse buttons
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)InputsManager::mouseButtonCallbackStatic);

    // Initializing the mouse position
    std::cout << "Initializing the mouse positions" << std::endl;
    glfwSetCursorPosCallback(window, InputsManager::cursorPositionCallbackStatic);

    // Initializing the scrolling
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetScrollCallback(window, InputsManager::scrollCallbackStatic);

    // Initializing the mouse focus
    std::cout << "Initializing the mouse focus" << std::endl;
    glfwSetCursorEnterCallback(window, InputsManager::mouseEnterWindowCallbackStatic);

    glfwSetJoystickCallback((GLFWjoystickfun)InputsManager::joystickCallbackStatic);
    // Creating some test events
    // TODO: Delete this tests
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::Z,std::vector<InputAction>(InputAction::MoveForward)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::S,std::vector<InputAction>(InputAction::MoveBackward)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::Q,std::vector<InputAction>(InputAction::MoveLeft)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::D,std::vector<InputAction>(InputAction::MoveRight)));
}

InputsManager::~InputsManager(){

}

void InputsManager::keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void InputsManager::keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    // Don't wanna use the repeat action
    if(action == InputState::Repeat) return;
    LOG("---------------------------------");
    LOG ("window = " << window);
    switch (action) {
        case InputState::Press :
            WRITE("Pressing ");
            break;
        case InputState::Repeat :
            WRITE("Holding ");
            break;
        case InputState::Release :
            WRITE("Releasing ");
            break;
    }
    auto keyName = glfwGetKeyName((int)key, scancode);
    if (keyName != nullptr) {
        WRITE("the key " << keyName << " ");
    } else {
        WRITE("an unknown key of code " << key << " ");
    }

    if (mods & InputModifier::Alt) {
        WRITE("with Alt ");
    }
    if (mods & InputModifier::CapsLock) {
        WRITE("with CapsLock ");
    }
    if (mods & InputModifier::Ctrl) {
        WRITE("with Control ");
    }
    if (mods & InputModifier::NumLock) {
        WRITE("with NumLock ");
    }
    if (mods & InputModifier::Shift) {
        WRITE("with Shift ");
    }
    if (mods & InputModifier::Super) {
        WRITE("with Super ");
    }

    WRITE("");

    if (keyboardEvent.count(key) == 0) {
        LOG("No event found...");
    } else {
        for (auto & event : keyboardEvent[key]) {
            auto & input = inputEvents.at(event);
            float direction = input.positive ? 1.0f : -1.0f;
            float final = input.container.getFloat(input.props) + (action == InputState::Press ? direction*1.0f : direction * -1.0f);
            input.container.setValue(final, input.props);
        }
    }
    WRITE("---------------------------------");



}

void InputsManager::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {
    InputsManager::instance().cursorPositionCallback(window, xpos, ypos);
}

void InputsManager::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    this->mousePosition = glm::dvec2 {xpos, ypos};
//    LOG("MousePosition: " << glm::to_string(this->mousePosition));
}

void InputsManager::mouseButtonCallbackStatic(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    InputsManager::instance().mouseButtonCallback(window, button, action, mods);
}

void InputsManager::mouseButtonCallback(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    // Don't wanna use the repeat action
    if(action == InputState::Repeat) return;

    LOG("---------------------------------");
    LOG("window = " << window);
    switch (action) {
        case InputState::Press :
            WRITE("Pressing ");
            break;
        case InputState::Repeat :
            WRITE("Holding ");
            break;
        case InputState::Release :
            WRITE("Releasing ");
            break;
    }

    std::cout << "the mouse button " << button << " ";

    if (mods & InputModifier::Alt) {
        WRITE("witt Alt");
    }
    if (mods & InputModifier::CapsLock) {
        WRITE("with CapsLock ");
    }
    if (mods & InputModifier::Ctrl) {
        WRITE("with Control ");
    }
    if (mods & InputModifier::NumLock) {
        WRITE("with NumLock ");
    }
    if (mods & InputModifier::Shift) {
        WRITE("with Shift ");
    }
    if (mods & InputModifier::Super) {
        WRITE("with Super ");
    }

    LOG("");
    LOG("---------------------------------");
}

void InputsManager::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {
    InputsManager::instance().scrollCallback(window, xoffset, yoffset);
}

void InputsManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scrolling = glm::dvec2 {xoffset, yoffset};
    LOG("Scrolling of " << glm::to_string(this->scrolling));
}

void InputsManager::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {
    InputsManager::instance().mouseEnterWindowCallback(window, entered);
}

void InputsManager::mouseEnterWindowCallback(GLFWwindow *window, int entered) {
    if (entered) {
        LOG("The cursor is inside the application window.");
    } else {
        LOG("The cursor is outside the application window.");
    }
}

void InputsManager::joystickCallbackStatic(Joystick joystickId, int event) {
    InputsManager::instance().joystickCallback(joystickId, event);
}

void InputsManager::joystickCallback(Joystick jid, int event) {
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
void InputsManager::update() {
//    LOG("There is " << this->joystickConnected.size() << "Joystick connected.");
    for (auto & joystick : this->joystickConnected) {
        int jid = (int)joystick;
        LOG("---------------------------------");
        const char* alias = glfwGetJoystickName(jid);
        LOG("Joystick " << jid << " alias " << alias);

        // GUID:
        const char* guid = glfwGetJoystickGUID(jid);
        LOG("GUID = " << guid);

        // Logging the different axis
        int axisCount;
        const float* axes = glfwGetJoystickAxes(jid, &axisCount);
        for (int i = 0; i < axisCount; ++i) {
            LOG("Axis " << i << " = " << axes[i]);
        }

        // Logging the different buttons
        int buttonCount;
        const unsigned char* buttons = glfwGetJoystickButtons(jid, &buttonCount);
        for (int i = 0; i < buttonCount; ++i) {
            LOG("Button " << i << " = " << buttons[i]);
        }
        LOG("---------------------------------");

    }
}
