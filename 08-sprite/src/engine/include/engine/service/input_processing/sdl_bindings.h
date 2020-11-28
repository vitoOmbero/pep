#ifndef INC_05_GUESS_NUMBER_SDL_BINDINGS_H
#define INC_05_GUESS_NUMBER_SDL_BINDINGS_H

#include <SDL_keycode.h>

#include "keys.h"



inline static const std::unordered_map<SDL_Scancode , KeyName> sdlk_bindings{
        {SDL_SCANCODE_Q, KeyName::kQ},
        {SDL_SCANCODE_W, KeyName::kW},
        {SDL_SCANCODE_E, KeyName::kE},
        {SDL_SCANCODE_R, KeyName::kR},
        {SDL_SCANCODE_T, KeyName::kT},
        {SDL_SCANCODE_Y, KeyName::kY},
        {SDL_SCANCODE_U, KeyName::kU},
        {SDL_SCANCODE_I, KeyName::kI},
        {SDL_SCANCODE_O, KeyName::kO},
        {SDL_SCANCODE_P, KeyName::kP},
        {SDL_SCANCODE_A, KeyName::kA},
        {SDL_SCANCODE_S, KeyName::kS},
        {SDL_SCANCODE_D, KeyName::kD},
        {SDL_SCANCODE_F, KeyName::kF},
        {SDL_SCANCODE_G, KeyName::kG},
        {SDL_SCANCODE_H, KeyName::kH},
        {SDL_SCANCODE_J, KeyName::kJ},
        {SDL_SCANCODE_K, KeyName::kK},
        {SDL_SCANCODE_L, KeyName::kL},
        {SDL_SCANCODE_Z, KeyName::kZ},
        {SDL_SCANCODE_X, KeyName::kX},
        {SDL_SCANCODE_C, KeyName::kC},
        {SDL_SCANCODE_V, KeyName::kV},
        {SDL_SCANCODE_B, KeyName::kB},
        {SDL_SCANCODE_N, KeyName::kN},
        {SDL_SCANCODE_M, KeyName::kM},

        {SDL_SCANCODE_0, KeyName::k0},
        {SDL_SCANCODE_1, KeyName::k1},
        {SDL_SCANCODE_2, KeyName::k2},
        {SDL_SCANCODE_3, KeyName::k3},
        {SDL_SCANCODE_4, KeyName::k4},
        {SDL_SCANCODE_5, KeyName::k5},
        {SDL_SCANCODE_6, KeyName::k6},
        {SDL_SCANCODE_7, KeyName::k7},
        {SDL_SCANCODE_8, KeyName::k8},
        {SDL_SCANCODE_9, KeyName::k9},

        {SDL_SCANCODE_GRAVE, KeyName::kBackquote},
        {SDL_SCANCODE_MINUS, KeyName::kMinus},
        {SDL_SCANCODE_EQUALS, KeyName::kEquals},

        {SDL_SCANCODE_ESCAPE, KeyName::kEsc},
        {SDL_SCANCODE_TAB, KeyName::kTab},

        {SDL_SCANCODE_LCTRL, KeyName::kCtrlLeft},
        {SDL_SCANCODE_RCTRL, KeyName::kCtrlRight},
        {SDL_SCANCODE_SPACE, KeyName::kSpace},
        {SDL_SCANCODE_CAPSLOCK, KeyName::kCapsLk},

        {SDL_SCANCODE_LALT, KeyName::kAltLeft},
        {SDL_SCANCODE_RALT, KeyName::kAltRight},
        {SDL_SCANCODE_RETURN, KeyName::kEnter},

        {SDL_SCANCODE_LSHIFT, KeyName::kShiftLeft},
        {SDL_SCANCODE_RSHIFT, KeyName::kShiftRight},
        {SDL_SCANCODE_BACKSPACE, KeyName::kBackSpace},
        {SDL_SCANCODE_DELETE, KeyName::kDelete},
        {SDL_SCANCODE_INSERT, KeyName::kInsert},
        {SDL_SCANCODE_PRINTSCREEN, KeyName::kPrtSc},
        {SDL_SCANCODE_HOME, KeyName::kHome},
        {SDL_SCANCODE_END, KeyName::kEnd},
        {SDL_SCANCODE_PAGEUP, KeyName::kPgUp},
        {SDL_SCANCODE_PAGEDOWN, KeyName::kPgDn},

        {SDL_SCANCODE_LEFT, KeyName::kArrowLeft},
        {SDL_SCANCODE_RIGHT, KeyName::kArrowRight},
        {SDL_SCANCODE_UP, KeyName::kArrowUp},
        {SDL_SCANCODE_DOWN, KeyName::kArrowDown},

};

#endif //INC_05_GUESS_NUMBER_SDL_BINDINGS_H
