//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_TO_STRING_H
#define INC_01_GUESS_NUMBER_PROTO_TO_STRING_H

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "version.h"

struct GameInstanceStrings {
    const std::string title;
    const std::string default_filler;
};

struct DescriptionStrings {
    const std::string version;
    const std::string input_tip;
};

struct StringRegistry {
    DescriptionStrings description_strings;
};

namespace Culture {
    enum Language {
        kEn,
        kRu
    };

    inline static const std::unordered_map<Language, StringRegistry> strings = { // NOLINT(cert-err58-cpp)
            {kEn, {"Version", "Press enter to continue..."}},
            {kRu, {"Версия",  "Нажмиет Enter, чтобы продолжить..."}}
    };
}

static std::string ToString(Version ver, Culture::Language lang = Culture::kEn) {
    std::ostringstream oss;
    oss <<
        Culture::strings.at(lang).description_strings.version <<
        " " <<
        std::to_string(ver.major) << "." << std::to_string(ver.minor) << "." << std::to_string(ver.patch);
    return oss.str();
}


#endif //INC_01_GUESS_NUMBER_PROTO_TO_STRING_H
