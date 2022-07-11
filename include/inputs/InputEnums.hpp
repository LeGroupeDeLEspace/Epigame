//
// Created by Iannis on 21/06/2022.
//

#ifndef JEUDELESPACE_INPUTENUMS_HPP
#define JEUDELESPACE_INPUTENUMS_HPP
#include "GLFW/glfw3.h"
#include <ostream>
namespace Input {
    enum State : int {
        Press = GLFW_PRESS,
        Repeat = GLFW_REPEAT,
        Release = GLFW_RELEASE,
    };
    enum Modifier : int {
        Shift = GLFW_MOD_SHIFT,
        Alt = GLFW_MOD_ALT,
        Ctrl = GLFW_MOD_CONTROL,
        Super = GLFW_MOD_SUPER,
        CapsLock = GLFW_MOD_CAPS_LOCK,
        NumLock = GLFW_MOD_NUM_LOCK,
    };
}

namespace Keyboard {
    enum KeyCode : int {

/* The unknown key */
        Unknown = GLFW_KEY_UNKNOWN,

/* Printable keys */
        Space = GLFW_KEY_SPACE,
        Apostrophe = GLFW_KEY_APOSTROPHE,/* ' */
        Comma = GLFW_KEY_COMMA,/* , */
        Minus = GLFW_KEY_MINUS,/* - */
        Period = GLFW_KEY_PERIOD,/* . */
        Slash = GLFW_KEY_SLASH,/* / */
        Keyboard_0 = GLFW_KEY_0,
        Keyboard_1 = GLFW_KEY_1,
        Keyboard_2 = GLFW_KEY_2,
        Keyboard_3 = GLFW_KEY_3,
        Keyboard_4 = GLFW_KEY_4,
        Keyboard_5 = GLFW_KEY_5,
        Keyboard_6 = GLFW_KEY_6,
        Keyboard_7 = GLFW_KEY_7,
        Keyboard_8 = GLFW_KEY_8,
        Keyboard_9 = GLFW_KEY_9,
        Semicolon = GLFW_KEY_SEMICOLON,/* ; */
        Equal = GLFW_KEY_EQUAL,/* = */
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        Left_Bracket = GLFW_KEY_LEFT_BRACKET,/* [ */
        Backslash = GLFW_KEY_BACKSLASH,/* \ */
        Right_Bracket = GLFW_KEY_RIGHT_BRACKET,/* ] */
        Grave_Accent = GLFW_KEY_GRAVE_ACCENT,/* ` */
        World_1 = GLFW_KEY_WORLD_1,/* NON-US #1 */
        World_2 = GLFW_KEY_WORLD_2,/* NON-US #2 */

/* Function keys */
        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        Tab = GLFW_KEY_TAB,
        Backspace = GLFW_KEY_BACKSPACE,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,
        Right = GLFW_KEY_RIGHT,
        Left = GLFW_KEY_LEFT,
        Down = GLFW_KEY_DOWN,
        Up = GLFW_KEY_UP,
        Page_Up = GLFW_KEY_PAGE_UP,
        Page_Down = GLFW_KEY_PAGE_DOWN,
        Home = GLFW_KEY_HOME,
        End = GLFW_KEY_END,
        Caps_Lock = GLFW_KEY_CAPS_LOCK,
        Scroll_Lock = GLFW_KEY_SCROLL_LOCK,
        Num_Lock = GLFW_KEY_NUM_LOCK,
        Print_Screen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
        Kp_0 = GLFW_KEY_KP_0,
        Kp_1 = GLFW_KEY_KP_1,
        Kp_2 = GLFW_KEY_KP_2,
        Kp_3 = GLFW_KEY_KP_3,
        Kp_4 = GLFW_KEY_KP_4,
        Kp_5 = GLFW_KEY_KP_5,
        Kp_6 = GLFW_KEY_KP_6,
        Kp_7 = GLFW_KEY_KP_7,
        Kp_8 = GLFW_KEY_KP_8,
        Kp_9 = GLFW_KEY_KP_9,
        Kp_Decimal = GLFW_KEY_KP_DECIMAL,
        Kp_Divide = GLFW_KEY_KP_DIVIDE,
        Kp_Multiply = GLFW_KEY_KP_MULTIPLY,
        Kp_Subtract = GLFW_KEY_KP_SUBTRACT,
        Kp_Add = GLFW_KEY_KP_ADD,
        Kp_Enter = GLFW_KEY_KP_ENTER,
        Kp_Equal = GLFW_KEY_KP_EQUAL,
        Left_Shift = GLFW_KEY_LEFT_SHIFT,
        Left_Control = GLFW_KEY_LEFT_CONTROL,
        Left_Alt = GLFW_KEY_LEFT_ALT,
        Left_Super = GLFW_KEY_LEFT_SUPER,
        Right_Shift = GLFW_KEY_RIGHT_SHIFT,
        Right_Control = GLFW_KEY_RIGHT_CONTROL,
        Right_Alt = GLFW_KEY_RIGHT_ALT,
        Right_Super = GLFW_KEY_RIGHT_SUPER,
        Menu = GLFW_KEY_MENU,

        Last_Keycode = GLFW_KEY_LAST,

    };
}

namespace Mouse {
    enum Button : int {
        M1 = GLFW_MOUSE_BUTTON_1,
        M2 = GLFW_MOUSE_BUTTON_2,
        M3 = GLFW_MOUSE_BUTTON_3,
        M4 = GLFW_MOUSE_BUTTON_4,
        M5 = GLFW_MOUSE_BUTTON_5,
        M6 = GLFW_MOUSE_BUTTON_6,
        M7 = GLFW_MOUSE_BUTTON_7,
        M8 = GLFW_MOUSE_BUTTON_8,
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Right = GLFW_MOUSE_BUTTON_RIGHT,
        Middle = GLFW_MOUSE_BUTTON_MIDDLE,
        Last_Button = GLFW_MOUSE_BUTTON_LAST,
    };

    enum Axis : int {
        Position,
        DeltaMovement,
        DeltaScroll,
    };
}

namespace Joystick {
    enum JoystickId : int {
        J1 = GLFW_JOYSTICK_1,
        J2 = GLFW_JOYSTICK_2,
        J3 = GLFW_JOYSTICK_3,
        J4 = GLFW_JOYSTICK_4,
        J5 = GLFW_JOYSTICK_5,
        J6 = GLFW_JOYSTICK_6,
        J7 = GLFW_JOYSTICK_7,
        J8 = GLFW_JOYSTICK_8,
        J9 = GLFW_JOYSTICK_9,
        J10 = GLFW_JOYSTICK_10,
        J11 = GLFW_JOYSTICK_11,
        J12 = GLFW_JOYSTICK_12,
        J13 = GLFW_JOYSTICK_13,
        J14 = GLFW_JOYSTICK_14,
        J15 = GLFW_JOYSTICK_15,
        J16 = GLFW_JOYSTICK_16,
        Last_Jid = GLFW_JOYSTICK_LAST,
    };
}

namespace Gamepad {
    enum Button : int {
        A = GLFW_GAMEPAD_BUTTON_A,
        B = GLFW_GAMEPAD_BUTTON_B,
        X = GLFW_GAMEPAD_BUTTON_X,
        Y = GLFW_GAMEPAD_BUTTON_Y,
        Left_Bumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        Right_Bumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
        Back = GLFW_GAMEPAD_BUTTON_BACK,
        Start = GLFW_GAMEPAD_BUTTON_START,
        Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
        Left_Thumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        Right_Thumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
        Dpad_Up = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        Dpad_Right = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        Dpad_Down = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        Dpad_Left = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
        Last_Button = GLFW_GAMEPAD_BUTTON_LAST,
    };

    enum Axis : int {
        Left_X = GLFW_GAMEPAD_AXIS_LEFT_X,
        Left_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
        Right_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
        Right_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
        Left_Trigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
        Right_Trigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
        Last_Axis = GLFW_GAMEPAD_AXIS_LAST,
    };
}


#endif //JEUDELESPACE_INPUTENUMS_HPP
