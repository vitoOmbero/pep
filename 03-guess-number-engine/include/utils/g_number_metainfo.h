//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_G_NUMBER_METAINFO_H
#define INC_03_GUESS_NUMBER_G_NUMBER_METAINFO_H

#include "utils/engine_assets.h"
#include "game_description.h"

namespace GuessNumber{
    inline static const std::unordered_map<Culture::Language, GameDescriptionStrings> game_description_strings = { // NOLINT(cert-err58-cpp)
            {Culture::kEn, {"Guess The FNumber", "$", "Bye-bye! See you later!"}},
            {Culture::kRu, {"Угадай БЧисло",     "@"}}
    };

    inline static const GameDescriptionInfo gdi{
            "guess_num",
            {0, 1, 2},
            0,
            4
    };
}

#endif //INC_03_GUESS_NUMBER_G_NUMBER_METAINFO_H
