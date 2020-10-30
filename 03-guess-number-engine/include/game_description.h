//
// Created by vito on 29.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H
#define INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H

#include <string>

#include "version.h"
#include "level.h"

struct GameDescriptionInfo{
    std::string project_work_name;
    Version version;
    level_id_t entry_point;
    level_id_t exit_point;
};


struct GameDescriptionStrings {
    const std::string title;
    const std::string default_filler;
    const std::string bye_bye_msg = "";
};

#endif //INC_03_GUESS_NUMBER_GAME_DESCRIPTION_H
