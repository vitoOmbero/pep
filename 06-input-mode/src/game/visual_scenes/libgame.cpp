#include "libgame.h"

#include "doctest.h"
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "visual_scenes/assets.h"
#include "visual_scenes/logic.h"
#include "visual_scenes/metainfo.h"
#include "symbol_export.h"

PEP_DECLSPEC const GameDescriptionInfo* game::getDescriptionInfo() {
  return &VisualScenes::gdi;
}

PEP_DECLSPEC const
    std::unordered_map<Culture::Language, GameDescriptionStrings>*
    game::getDescriptionStrings() {
  return &VisualScenes::game_description_strings;
}

PEP_DECLSPEC
const std::unordered_map<Culture::Language, std::vector<std::string>>*
game::getStringAssets() {
  return &VisualScenes::Assets::game_assets_strings;
}

PEP_DECLSPEC const std::vector<VariableDeclaration>*
game::getGlobalVariableDeclarations() {
  return &VisualScenes::Logic::GlobalVariables::declaration;
}

PEP_DECLSPEC const std::vector<Level>* game::getLevels() {
  return &VisualScenes::Logic::guess_number_levels;
}

PEP_DECLSPEC Culture::Language game::getLanguage() { return Culture::kEn; }

PEP_DECLSPEC AssetsLoadingStrategy game::getAssetsLoadingStrategy() {
  return AssetsLoadingStrategy::kCompileTimeBuiltInAssets;
}

TEST_CASE("visual_scenes") { printf("I am a test from the Visual Scenes!\n"); }