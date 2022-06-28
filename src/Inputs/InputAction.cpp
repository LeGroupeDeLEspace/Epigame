//
// Created by Iannis on 28/06/2022.
//

#include <string>
#include <cstring>
#include <stdexcept>
#include "Inputs/InputEvent.hpp"

InputAction InputActionHelper::GetInputAction(const char* action) {
    for (int i = 0; i < InputAction::Count; ++i) {
        if (strcmp(action,InputActionName[i]) == 0){
            return static_cast<InputAction>(i);
        }
    }

    throw std::runtime_error(std::string("The action \"").append(action).append("\" was not found."));
}