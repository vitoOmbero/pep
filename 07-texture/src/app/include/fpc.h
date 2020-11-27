//
// Created by vito on 18.11.20.
//

#ifndef INC_05_GUESS_NUMBER_FPC_H
#define INC_05_GUESS_NUMBER_FPC_H

#include "engine/engine_func_load.h"
#include "game/game_func_load.h"

namespace game_fpc {
bool Init(game_loaded_ptrs function_pointers_container);

bool IsInited();

const game_loaded_ptrs& Get();
}  // namespace game_fpc

namespace engine_fpc {
bool Init(engine_loaded_ptrs function_pointers_container);

bool IsInited();

const engine_loaded_ptrs& Get();
}  // namespace engine_fpc

#endif  // INC_05_GUESS_NUMBER_FPC_H
