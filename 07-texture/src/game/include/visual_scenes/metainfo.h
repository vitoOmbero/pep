#ifndef INC_META_INFO_H
#define INC_META_INFO_H

#include <unordered_map>

#include "engine/pep.h"

namespace VisualScenes {
inline const std::unordered_map<Culture::Language,
                                GameDescriptionStrings>
    game_description_strings = {  // NOLINT(cert-err58-cpp)
        {Culture::kEn, {{"Visual Demo"}, {"$"}, {"Bye-bye! See you later!"}}},
        {Culture::kRu, {{"Визуальное демо"}, {"@"}}}};

inline const GameDescriptionInfo gdi{{"visual_scenes"}, {0, 1, 2}, 0, 4};
}

#endif
