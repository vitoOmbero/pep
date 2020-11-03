//
// Created by vito on 31.10.20.
//

#include "assets_loader.h"

#include "utils/g_number_assets.h"
#include "utils/g_number_logic.h"
#include "utils/g_number_metainfo.h"

void AssetsLoader::LoadStaticAssetsForGuessNumber(Culture::Language lang) {
  Game::Language = lang;
  Game::DescriptionInfo = &GuessNumber::gdi;
  Game::DescriptionStrings = &GuessNumber::game_description_strings;
  Game::StringAssets = &GuessNumber::Assets::game_assets_strings;
  Game::GlobalVariableDeclarations =
      &GuessNumber::Logic::GlobalVariables::declaration;
  Game::Levels = &GuessNumber::Logic::guess_number_levels;

#ifdef PEP_DEBUG
  Terminal::ReportErr(GuessNumber::gdi.project_work_name);
  Terminal::ReportErr(Game::DescriptionInfo->project_work_name);

  Terminal::ReportErr((void *)Game::DescriptionInfo);
  Terminal::ReportErr((void *)Game::DescriptionStrings);
  Terminal::ReportErr((void *)Game::StringAssets);
  Terminal::ReportErr((void *)Game::GlobalVariableDeclarations);
  Terminal::ReportErr((void *)Game::Levels);

#endif
}
