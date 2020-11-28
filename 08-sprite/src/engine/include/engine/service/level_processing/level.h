#ifndef INC_03_GUESS_NUMBER_LEVEL_H
#define INC_03_GUESS_NUMBER_LEVEL_H

#include <unordered_map>
#include <variant>
#include <vector>

#include "action.h"
#include "engine/service/glrenderer/game_objects.h"
#include "engine/service/text_world/game_objects.h"

using index_t = size_t;
using level_id_t = size_t;

struct GameLevelLogic {
  using callback_t = void (*)();

  callback_t OnLoad;
  callback_t ExecuteTextWorldLogic;
  callback_t Transition;
};

struct Level {
  std::vector<index_t> asset_string_ids;
  std::vector<text_world_objects::Type> text_world_objects;
  GameLevelLogic game_logic;
  std::vector<visual_world_objects::Type> visual_world_objects{};
};

#endif  // INC_03_GUESS_NUMBER_LEVEL_H
