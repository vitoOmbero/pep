#include "libgame.h"

#include "doctest.h"
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "g_number/assets.h"
#include "g_number/logic.h"
#include "g_number/metainfo.h"
#include "symbol_export.h"

PEP_DECLSPEC const GameDescriptionInfo* game::getDescriptionInfo() {
  return &GuessNumber::gdi;
}

PEP_DECLSPEC const
    std::unordered_map<Culture::Language, GameDescriptionStrings>*
    game::getDescriptionStrings() {
  return &GuessNumber::game_description_strings;
}

PEP_DECLSPEC
const std::unordered_map<Culture::Language, std::vector<std::string>>*
game::getStringAssets() {
  return &GuessNumber::Assets::game_assets_strings;
}

PEP_DECLSPEC const std::vector<VariableDeclaration>*
game::getGlobalVariableDeclarations() {
  return &GuessNumber::Logic::GlobalVariables::declaration;
}

PEP_DECLSPEC const std::vector<Level>* game::getLevels() {
  return &GuessNumber::Logic::guess_number_levels;
}

PEP_DECLSPEC Culture::Language game::getLanguage() { return Culture::kEn; }

PEP_DECLSPEC AssetsLoadingStrategy game::getAssetsLoadingStrategy() {
  return AssetsLoadingStrategy::kCompileTimeBuiltInAssets;
}

TEST_CASE("game_guess_number") { printf("I am a test from the GNumber!\n"); }