#include "Inputs/Inputs.hpp"
#include <iostream>
#include "TestWindow.hpp"
#include <glm/gtx/string_cast.hpp>
#include <algorithm>

class DebugCommand0 : public Command0 {
public:
    DebugCommand0() {
        this->str = "Hello World !";
    }
    DebugCommand0(const std::string str) {
        this->str = str;
    }

    std::string str;
    void execute() override {
        std::cout << str << std::endl;
    }
};

Inputs::Inputs() : keyboardEvent(), eventAction(), joystickConnected() {
    //Get the windows
    GLFWwindow* window = TestWindow::getCurrentWindow();

    // Initializing the keyboards inputs
    std::cout << "Initializing the keyboard inputs" << std::endl;
    glfwSetKeyCallback(window, (GLFWkeyfun)(Inputs::keyCallbackStatic));

    // Initializing the mouse buttons
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)Inputs::mouseButtonCallbackStatic);

    // Initializing the mouse position
    std::cout << "Initializing the mouse positions" << std::endl;
    glfwSetCursorPosCallback(window, Inputs::cursorPositionCallbackStatic);

    // Initializing the scrolling
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetScrollCallback(window, Inputs::scrollCallbackStatic);

    // Initializing the mouse focus
    std::cout << "Initializing the mouse focus" << std::endl;
    glfwSetCursorEnterCallback(window, Inputs::mouseEnterWindowCallbackStatic);

    glfwSetJoystickCallback((GLFWjoystickfun)Inputs::joystickCallbackStatic);
    // Creating some test events
    // TODO: Delete this tests
    this->keyboardEvent.insert(std::make_pair<KeyCode,std::vector<std::string>>(KeyCode::Space,std::vector<std::string>(1,"hello")));
    this->eventAction.insert(std::make_pair<std::string, Command0*>("hello", new DebugCommand0{"Hello, you press the Space Bar"}));
}

Inputs::~Inputs(){

}

void Inputs::keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void Inputs::keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "window = " << window << std::endl;
    switch (action) {
        case InputState::Press :
            std::cout << "Pressing ";
            break;
        case InputState::Hold :
            std::cout << "Holding ";
            break;
        case InputState::Release :
            std::cout << "Releasing ";
            break;
    }
    auto keyName = glfwGetKeyName((int)key, scancode);
    if (keyName != nullptr) {
        std::cout << "the key " << keyName << " ";
    } else {
        std::cout << "an unknown key of code " << key << " ";
    }

    if (mods & InputModifier::Alt) {
        std::cout << "with Alt ";
    }
    if (mods & InputModifier::CapsLock) {
        std::cout << "with CapsLock ";
    }
    if (mods & InputModifier::Ctrl) {
        std::cout << "with Control ";
    }
    if (mods & InputModifier::NumLock) {
        std::cout << "with NumLock ";
    }
    if (mods & InputModifier::Shift) {
        std::cout << "with Shift ";
    }
    if (mods & InputModifier::Super) {
        std::cout << "with Super ";
    }

    std::cout << std::endl;

    if (keyboardEvent.count(key) == 0) {
        std::cout << "No event found..." << std::endl;
    } else {
        for (auto & event : keyboardEvent[key]) {
            std::cout << "Starting the event " << event << std::endl;
            eventAction[event]->execute();
            std::cout << "Ending the event " << event << std::endl;
        }
    }
    std::cout << "---------------------------------" << std::endl;
}

void Inputs::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {
    Inputs::instance().cursorPositionCallback(window, xpos, ypos);
}

void Inputs::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    this->mousePosition = glm::dvec2 {xpos, ypos};
    std::cout << "MousePosition: " << glm::to_string(this->mousePosition) << std::endl;
}

void Inputs::mouseButtonCallbackStatic(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    Inputs::instance().mouseButtonCallback(window,button,action,mods);
}

void Inputs::mouseButtonCallback(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {

    std::cout << "---------------------------------" << std::endl;
    std::cout << "window = " << window << std::endl;
    switch (action) {
        case InputState::Press :
            std::cout << "Pressing ";
            break;
        case InputState::Hold :
            std::cout << "Holding ";
            break;
        case InputState::Release :
            std::cout << "Releasing ";
            break;
    }

    std::cout << "the mouse button " << button << " ";

    if (mods & InputModifier::Alt) {
        std::cout << "with Alt ";
    }
    if (mods & InputModifier::CapsLock) {
        std::cout << "with CapsLock ";
    }
    if (mods & InputModifier::Ctrl) {
        std::cout << "with Control ";
    }
    if (mods & InputModifier::NumLock) {
        std::cout << "with NumLock ";
    }
    if (mods & InputModifier::Shift) {
        std::cout << "with Shift ";
    }
    if (mods & InputModifier::Super) {
        std::cout << "with Super ";
    }

    std::cout << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void Inputs::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {
    Inputs::instance().scrollCallback(window, xoffset, yoffset);
}

void Inputs::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scrolling = glm::dvec2 {xoffset, yoffset};
    std::cout << "Scrolling of " << glm::to_string(this->scrolling) << std::endl;
}

void Inputs::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {
    Inputs::instance().mouseEnterWindowCallback(window, entered);
}

void Inputs::mouseEnterWindowCallback(GLFWwindow *window, int entered) {
    if (entered) {
        std::cout << "The cursor is inside the application window." << std::endl;
    } else {
        std::cout << "The cursor is outside the application window." << std::endl;
    }
}

void Inputs::joystickCallbackStatic(Joystick joystickId, int event) {
    Inputs::instance().joystickCallback(joystickId, event);
}

void Inputs::joystickCallback(Joystick jid, int event) {
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
        std::cout << name << " has been connected." << std::endl;
    }
    else if (event == GLFW_DISCONNECTED)
    {
        // The joystick was disconnected
        std::cout << name << " has been disconnected." << std::endl;
        auto index = std::find(this->joystickConnected.begin(), this->joystickConnected.end(),jid);
        if (index != this->joystickConnected.end()) {
            this->joystickConnected.erase(index);
        } else {
            std::cout << "The joystick " << name << " hasn't been connected";
        }
    }
}

// Updating the joystick
void update() {

}