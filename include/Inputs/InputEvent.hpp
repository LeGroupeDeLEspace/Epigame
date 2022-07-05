//
// Created by Iannis on 14/06/2022.
//

#ifndef JEUDELESPACE_INPUTEVENT_HPP
#define JEUDELESPACE_INPUTEVENT_HPP

#include <string>
namespace Input {
    enum Action {
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
        // Jump
        JumpAction,
        Count,
    };

    enum Event {
        Move,
        Look,
        Accelerate,
        Decelerate,
        Jump,
        //TODO: Add more ?
    };
}

extern const char* InputActionName[Input::Action::Count];

namespace InputActionHelper {
    Input::Action GetInputAction(const char* action);
}


#endif //JEUDELESPACE_INPUTEVENT_HPP
