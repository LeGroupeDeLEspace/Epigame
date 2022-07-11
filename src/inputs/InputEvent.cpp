//
// Created by Iannis on 28/06/2022.
//

#include <string>
#include <cstring>
#include <stdexcept>
#include "inputs/InputEvent.hpp"

const char* InputActionName[Input::Action::Count] = {
// Move Action
"MoveForward",
"MoveBackward",
"MoveRight",
"MoveLeft",
"MoveUp",
"MoveDown",
// LookAction
"LookRight",
"LookLeft",
"LookUp",
"LookDown",
"JumpAction",
};

Input::Action InputActionHelper::GetInputAction(const char* action) {
    for (int i = 0; i < Input::Action::Count; ++i) {
        if (strcmp(action, InputActionName[i]) == 0){
            return static_cast<Input::Action>(i);
        }
    }

    throw std::runtime_error(std::string("The action \"").append(action).append("\" was not found."));
}