#ifndef JEUDELESPACE_INPUTS_HPP
#define JEUDELESPACE_INPUTS_HPP

#include "Command.hpp"
#include "GLFW/glfw3.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "InputKey.hpp"

class Inputs {
private:
    std::unordered_map<std::string, std::vector<InputKey>> eventKey;
    std::unordered_map<std::string, Command0&> eventAction;

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
    Inputs();
public:
    ~Inputs();

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static Inputs& instance()
    {
        static auto *instance = new Inputs();
        return *instance;
    }

    // The functions for the rest of the
    void loadInputs(std::unordered_map<std::string, std::vector<InputKey>> inputs);
    void changeInput(std::string event, std::vector<InputKey> inputs);
    void addAction(std::string event, Command0& action);
    void addAction(std::string event, std::vector<Command0> actions);
    void removeAction(std::string event, Command0& action);
    void removeAction(std::string event, std::vector<Command0&> actions);
};
#endif //JEUDELESPACE_INPUTS_HPP
