//
// Created by Iannis on 14/06/2022.
//

#ifndef JEUDELESPACE_INPUTEVENT_HPP
#define JEUDELESPACE_INPUTEVENT_HPP

#include <string>

enum InputAction {
    // Move Action
    MoveForward,
    MoveBackward,
    MoveRight,
    MoveLeft,
    MoveUp,
    MoveDown,
    // LookAction
    LookRight,
    LookLeft,
    LookUp,
    LookDown,
    Count,
};

const char* InputActionName[InputAction::Count] {
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
};


namespace InputActionHelper {
    InputAction GetInputAction(const char* action);
}

enum InputEvent {
    Move,
    Look,
    Accelerate,
    Decelerate,
    //TODO: Add more ?
};

#endif //JEUDELESPACE_INPUTEVENT_HPP
