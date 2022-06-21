//
// Created by Iannis on 21/06/2022.
//

#include "Inputs/InputEnums.hpp"

std::ostream& operator<< (std::ostream& out, const InputState& inputState) {
    return out << ((int)inputState);
}

std::ostream& operator<< (std::ostream& out, const KeyCode& keycode) {
    return out << ((int)keycode);
}

std::ostream& operator<< (std::ostream& out, const InputModifier& inputModifier) {
    return out << ((int)inputModifier);
}

std::ostream& operator<< (std::ostream& out, const MouseButton& mouseButton) {
    return out << ((int)mouseButton);
}

std::ostream& operator<< (std::ostream& out, const Joystick& joystick) {
    return out << ((int)joystick);
}

std::ostream& operator<< (std::ostream& out, const GamepadButton& gamepadButton) {
    return out << ((int)gamepadButton);
}

std::ostream& operator<< (std::ostream& out, const GamepadAxis& gamepadAxis) {
    return out << ((int)gamepadAxis);
}