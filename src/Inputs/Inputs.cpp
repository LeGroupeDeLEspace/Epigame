#include "Inputs/Inputs.hpp"
#include <iostream>
#include "TestWindow.hpp"
#include <glm/gtx/string_cast.hpp>
#include <algorithm>

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

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

Inputs::Inputs() : keyboardEvent(), /*eventAction(),*/ joystickConnected() {
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
//    this->eventAction.insert(std::make_pair<std::string, Command0*>("hello", new DebugCommand0{"Hello, you press the Space Bar"}));
}

Inputs::~Inputs(){

}

void Inputs::keyCallbackStatic(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    instance().keyCallback(window, key, scancode, action, mods);
}

void Inputs::keyCallback(GLFWwindow* window, KeyCode key, int scancode, InputState action, InputModifier mods) {
    LOG("---------------------------------");
    LOG ("window = " << window);
    switch (action) {
        case InputState::Press :
            WRITE("Pressing ");
            break;
        case InputState::Hold :
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
            std::cout << "Suppose to start the event " << event << std::endl;
        }
    }
    WRITE("---------------------------------");
}

void Inputs::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {
    Inputs::instance().cursorPositionCallback(window, xpos, ypos);
}

void Inputs::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    this->mousePosition = glm::dvec2 {xpos, ypos};
    LOG("MousePosition: " << glm::to_string(this->mousePosition));
}

void Inputs::mouseButtonCallbackStatic(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {
    Inputs::instance().mouseButtonCallback(window,button,action,mods);
}

void Inputs::mouseButtonCallback(GLFWwindow *window, MouseButton button, InputState action, InputModifier mods) {

    LOG("---------------------------------");
    LOG("window = " << window);
    switch (action) {
        case InputState::Press :
            WRITE("Pressing ");
            break;
        case InputState::Hold :
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

void Inputs::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {
    Inputs::instance().scrollCallback(window, xoffset, yoffset);
}

void Inputs::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scrolling = glm::dvec2 {xoffset, yoffset};
    LOG("Scrolling of " << glm::to_string(this->scrolling));
}

void Inputs::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {
    Inputs::instance().mouseEnterWindowCallback(window, entered);
}

void Inputs::mouseEnterWindowCallback(GLFWwindow *window, int entered) {
    if (entered) {
        LOG("The cursor is inside the application window.");
    } else {
        LOG("The cursor is outside the application window.");
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
void Inputs::update() {
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