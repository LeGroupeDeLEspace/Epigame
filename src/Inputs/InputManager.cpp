#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <map>
#include "Inputs/InputEvent.hpp"
#include "Inputs/InputManager.hpp"
#include "TestWindow.hpp"

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

InputEventAction::InputEventAction(DataContainer& container, Axis props, bool positive): container(container), axis(props), positive(positive) {}

void onMove(DataContainer* container){
    LOG("The current movement is " << glm::to_string(container->getVec3()));
}

InputManager::InputManager() :
    joystickConnected(),
    keyboardEvent(),

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
    // Creating some test events
    // TODO: Delete this tests
    this->events.at(InputEvent::Move).addEvent(onMove);
    // The vector ain't kept
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::Z,std::vector<InputAction>(InputAction::MoveForward)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::S,std::vector<InputAction>(InputAction::MoveBackward)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::Q,std::vector<InputAction>(InputAction::MoveLeft)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::D,std::vector<InputAction>(InputAction::MoveRight)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::E,std::vector<InputAction>(InputAction::MoveUp)));
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<InputAction>>(KeyCode::A,std::vector<InputAction>(InputAction::MoveDown)));
}

InputManager::~InputManager(){

}

void InputManager::keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void InputManager::keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
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
    WRITE(std::endl);

    LOG("---");
    LOG("All the keyboardEvent");
    auto inputs = {KeyCode::Z, KeyCode::Q,KeyCode::S,KeyCode::D,KeyCode::A,KeyCode::E};
    for (const auto & input : inputs) {
        auto count = keyboardEvent.contains(input);
        LOG("For " << (char)input << " " << "found " << count << " event.");
        if(count) {
            auto actions = keyboardEvent.at(key);
            LOG("There is " << actions.size()<< " events :");
            for (const auto & inputAction : actions) {
                LOG("Event: \"" << InputActionName[inputAction] << "\"");
            }
            LOG("");
        }
    }
    LOG("---");


    auto eventFound = keyboardEvent.count(key);
    if (eventFound == 0) {
        LOG("No event found...");
    } else {
        LOG("Found " << eventFound << " events");
        for (auto & event : keyboardEvent.at(key)) {
            LOG("Updating the event " << InputActionName[event]);

            auto & input = inputEvents.at(event);
            auto containerType = input.container.type;

            if (containerType == DataType::Bool) {
                LOG("We update a boolean value");
                input.container.setData(action == InputState::Press);
            }
            else if (containerType % 2 == 0) { // Setting a float
                LOG("We update a float value");
                float direction = input.positive ? 1.0f : -1.0f;
                float final = input.container.getFloat(input.axis) +
                              (action == InputState::Press ? direction * 1.0f : direction * -1.0f);
                input.container.setValue(final, input.axis);
            } else { // is implicitly "containerType % 2 == 0" => setting an int
                LOG("We update a int value");
                int direction = input.positive ? 1 : -1;
                int final = input.container.getInt(input.axis) + (action == InputState::Press ? direction * 1 : direction * -1);
                input.container.setValue(final, input.axis);
            }
        }
    }
    WRITE("---------------------------------");
}

void InputManager::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {
    InputManager::instance().cursorPositionCallback(window, xpos, ypos);
}

void InputManager::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    this->mousePosition = glm::dvec2 {xpos, ypos};
//    LOG("MousePosition: " << glm::to_string(this->mousePosition));
}

void InputManager::mouseButtonCallbackStatic(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    InputManager::instance().mouseButtonCallback(window, button, action, mods);
}

void InputManager::mouseButtonCallback(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
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

void InputManager::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {
    InputManager::instance().scrollCallback(window, xoffset, yoffset);
}

void InputManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scrolling = glm::dvec2 {xoffset, yoffset};
    LOG("Scrolling of " << glm::to_string(this->scrolling));
}

void InputManager::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {
    InputManager::instance().mouseEnterWindowCallback(window, entered);
}

void InputManager::mouseEnterWindowCallback(GLFWwindow *window, int entered) {
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
