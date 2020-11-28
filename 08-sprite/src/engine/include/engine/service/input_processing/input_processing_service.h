#ifndef INC_05_GUESS_NUMBER_INPUT_PROCESSING_SERVICE_H
#define INC_05_GUESS_NUMBER_INPUT_PROCESSING_SERVICE_H

#include <SDL.h>

#include "keys.h"

namespace InputProcessingService {

void ProcessKeyboardEvent(const SDL_KeyboardEvent& sdl_keyboard_event);

void Init(const InputModeVector *modes);

void Destroy();

void EnableMode(size_t id);

}

#endif  // INC_05_GUESS_NUMBER_INPUT_PROCESSING_SERVICE_H
