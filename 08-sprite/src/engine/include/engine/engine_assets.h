//
// Created by vito on 29.10.20.
//

#ifndef INC_03_GUESS_NUMBER_ENGINE_ASSETS_H
#define INC_03_GUESS_NUMBER_ENGINE_ASSETS_H

#include <string>
#include <unordered_map>

struct DescriptionStrings {
  const std::string version;
  const std::string input_tip;
};

struct StringRegistry {
  DescriptionStrings description_strings;
};

namespace Culture {
enum Language { kEn, kRu };

inline const std::unordered_map<Language, StringRegistry> strings =
    {  // NOLINT(cert-err58-cpp)
        {kEn, {"Version", "Press enter to continue..."}},
        {kRu, {"Версия", "Нажмиет Enter, чтобы продолжить..."}}};
}  // namespace Culture

#endif  // INC_03_GUESS_NUMBER_ENGINE_ASSETS_H
