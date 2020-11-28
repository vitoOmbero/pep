#ifndef INC_05_GUESS_NUMBER_EVENT_H
#define INC_05_GUESS_NUMBER_EVENT_H

#include <variant>

#include "SDL_events.h"

using Event = std::variant<SDL_CommonEvent, SDL_QuitEvent, SDL_KeyboardEvent,
                           SDL_MouseMotionEvent, SDL_MouseButtonEvent>;

#endif  // INC_05_GUESS_NUMBER_EVENT_H
