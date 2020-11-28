//
// Created by vito on 29.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H
#define INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H

#include <string>

#include "engine/service/level_processing/level.h"
#include "version.h"

struct GameDescriptionInfo {
  std::string project_work_name;
  Version version;
  level_id_t entry_point;
  level_id_t exit_point;
};

struct GameDescriptionStrings {
  std::string title;
  std::string default_filler;
  std::string bye_bye_msg;
};

#endif  // INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H
