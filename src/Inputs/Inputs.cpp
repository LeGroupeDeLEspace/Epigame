#include "Inputs/Inputs.hpp"
#include "iostream"
#include "TestWindow.hpp"

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

Inputs::Inputs() : keyboardEvent(), eventAction() {
    //Get the windows
    GLFWwindow* window = TestWindow::getCurrentWindow();

    // Initializing the keyboards inputs
    std::cout << "Initializing the keyboard inputs" << std::endl;
    glfwSetKeyCallback(window, (GLFWkeyfun)(Inputs::keyCallbackStatic));

    // Initializing the mouse buttons
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetMouseButtonCallback(window, Inputs::mouseButtonCallbackStatic);

    // Initializing the mouse position
    std::cout << "Initializing the mouse positions" << std::endl;
    glfwSetCursorPosCallback(window, Inputs::cursorPositionCallbackStatic);

    // Initializing the scrolling
    std::cout << "Initializing the mouse buttons" << std::endl;
    glfwSetScrollCallback(window, Inputs::scrollCallbackStatic);

    // Initializing the mouse focus
    std::cout << "Initializing the mouse focus" << std::endl;
    glfwSetCursorEnterCallback(window, Inputs::mouseEnterWindowCallbackStatic);

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
    std::cout << "key = " << key << std::endl;
    std::cout << "scancode = " << scancode << std::endl;
    std::cout << "action = " << action << std::endl;
    std::cout << "mods = " << mods << std::endl;
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
    std::cout << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void Inputs::cursorPositionCallbackStatic(GLFWwindow *window, double xpos, double ypos) {

}

void Inputs::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

}

void Inputs::mouseButtonCallbackStatic(GLFWwindow *window, int button, int action, int mods) {

}

void Inputs::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

}

void Inputs::scrollCallbackStatic(GLFWwindow *window, double xoffset, double yoffset) {

}

void Inputs::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}

void Inputs::mouseEnterWindowCallbackStatic(GLFWwindow *window, int entered) {

}

void Inputs::mouseEnterWindowCallback(GLFWwindow *window, int entered) {

}
