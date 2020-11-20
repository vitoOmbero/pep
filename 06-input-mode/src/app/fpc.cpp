#include "fpc.h"

namespace {
game_loaded_ptrs game_fpc_impl;
bool is_game_fpc_inited = false;

engine_loaded_ptrs engine_fpc_impl;
bool is_engine_fpc_inited = false;
}  // namespace

bool game_fpc::Init(game_loaded_ptrs function_pointers_container) {
  if (is_game_fpc_inited) {
    return false;
  } else {
    game_fpc_impl = function_pointers_container;
    is_game_fpc_inited = true;
    return true;
  }
}

bool game_fpc::IsInited() { return is_game_fpc_inited; }

const game_loaded_ptrs &game_fpc::Get() { return game_fpc_impl; }

bool engine_fpc::Init(engine_loaded_ptrs function_pointers_container) {
  if (is_engine_fpc_inited) {
    return false;
  } else {
    engine_fpc_impl = function_pointers_container;
    is_engine_fpc_inited = true;
    return true;
  }
}

bool engine_fpc::IsInited() { return is_engine_fpc_inited; }

const engine_loaded_ptrs &engine_fpc::Get() { return engine_fpc_impl; }