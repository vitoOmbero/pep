//
// Created by vito on 31.10.20.
//

#ifndef INC_03_GUESS_NUMBER_ASSETS_LOADER_H
#define INC_03_GUESS_NUMBER_ASSETS_LOADER_H

#include <string>
#include <unordered_map>
#include <utility>

#include "assets_loader.h"
#include "game_description.h"
#include "utils/engine_assets.h"
#include "version.h"

// TODO: check for well-formed assets
class AssetsLoader {
 public:
  static void LoadStaticAssetsForGuessNumber(Culture::Language lang);
};

namespace Game {
inline const GameDescriptionInfo *DescriptionInfo;
inline const std::unordered_map<Culture::Language, GameDescriptionStrings>
    *DescriptionStrings;
inline const std::unordered_map<Culture::Language, std::vector<std::string>>
    *StringAssets;
inline const std::vector<VariableDeclaration> *GlobalVariableDeclarations;
inline const std::vector<Level> *Levels;
inline Culture::Language Language;

}  // namespace Game
#endif  // INC_03_GUESS_NUMBER_ASSETS_LOADER_H
