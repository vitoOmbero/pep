#ifndef GAMELOADLIB_LOAD_H
#define GAMELOADLIB_LOAD_HLOAD_H

#include <cstddef>
#include <cstdint>

#include "game/libgame.h"


namespace game_func_load::ptrs
{
using PrintHelloFromGame  = void(*)();
}

#ifndef PTRS_ONLY
namespace game_func_load::symbols
{
static const char* PrintHelloFromGame  = "hello_from_game";
}
#endif

#endif