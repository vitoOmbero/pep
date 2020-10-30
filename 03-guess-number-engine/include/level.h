//
// Created by vito on 29.10.20.
//

#ifndef INC_03_GUESS_NUMBER_LEVEL_H
#define INC_03_GUESS_NUMBER_LEVEL_H

#include <vector>
#include <variant>
#include <unordered_map>

#include "action.h"
#include "game_objects.h"
#include "game_level_logic_processor.h"

using index_t = size_t;
using level_id_t = size_t;

struct Level {
    std::vector<index_t> asset_string_ids;
    std::vector<text_world_objects::Type> text_world_objects;
    GameLevelLogic game_logic;
};

#endif //INC_03_GUESS_NUMBER_LEVEL_H
