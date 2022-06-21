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

bool operator& (int input, InputModifier other){
    return input & (int)other;
}

bool operator& (InputModifier input, int other){
    return (int)input & other;
}

bool operator& (InputModifier input, InputModifier other){
    return (int)input & (int)other;
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