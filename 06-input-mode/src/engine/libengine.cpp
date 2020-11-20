#include "engine/libengine.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#pragma clang diagnostic pop
#ifdef PEP_BUILD_TESTS
#include "doctest.h"
#endif
#ifdef PEP_BUILD_TESTS
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#endif
#include <iostream>
#ifdef PEP_BUILD_TESTS
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END
#endif

#include <SDL2/SDL.h>

#include "engine/service/level_processing/game_level_logic_processor.h"
#include "engine/service/variable_processing/template_string_processing.h"
#include "engine/symbol_export.h"
#include "utils/terminal.h"
#include "version.h"

namespace engine {

static std::string at_exit_message;

PEP_DECLSPEC void hello() {
  std::cout << "Hello from engine!" << std::endl;
  SDL_version compiled = {0, 0, 0};
  SDL_version linked = {0, 0, 0};

  SDL_VERSION(&compiled)
  SDL_GetVersion(&linked);

  std::cout << "SDL2 version: " << linked << std::endl;
  std::cout << "Engine version: " << EngineVersion << std::endl;

  if (SDL_COMPILEDVERSION !=
      SDL_VERSIONNUM(linked.major, linked.minor, linked.patch)) {
    std::cerr << "warning: SDL2 compiled and linked version mismatch: "
              << compiled << " " << linked << std::endl;
  }

  const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
  if (init_result != 0) {
    auto err_message = SDL_GetError();
    std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
  }
}

PEP_DECLSPEC [[maybe_unused]] void AtExit() {
  if (!at_exit_message.empty())
    Terminal::PrintBorderedText('+', at_exit_message);
}

PEP_DECLSPEC [[maybe_unused]] void Configure(EngineConfiguration cfg) {
  gEngineConfiguration = cfg;

#ifdef PEP_DEBUG
  std::cout << "Engine is configured with: " << cfg.placeholder << std::endl;
#endif

  Terminal::Init();

  /// TODO: stopped
}

PEP_DECLSPEC [[maybe_unused]] void SetGameConfiguration(GameConfiguration cfg) {
  gGameConfiguration = cfg;

  at_exit_message =
      gGameConfiguration.DescriptionStrings->at(gGameConfiguration.Language)
          .bye_bye_msg;

#ifdef PEP_DEBUG
  Terminal::ReportErr(cfg.DescriptionInfo->project_work_name);

  Terminal::ReportErr((void *)cfg.DescriptionInfo);
  Terminal::ReportErr((void *)cfg.DescriptionStrings);
  Terminal::ReportErr((void *)cfg.StringAssets);
  Terminal::ReportErr((void *)cfg.GlobalVariableDeclarations);
  Terminal::ReportErr((void *)cfg.Levels);
#endif

  GameVariablesService::global_vars.Add(
      *(gGameConfiguration.GlobalVariableDeclarations));

  GameLevelLogicProcessor::Init();
}

PEP_DECLSPEC [[maybe_unused]] void Play() {
#ifdef PEP_DEBUG
  Terminal::ReportMsg("Engine play() called...");
#endif
  GameLevelLogicProcessor::GetSingleton().ProcessLevel(
      gGameConfiguration.DescriptionInfo->entry_point);
}

}  // namespace engine

#ifdef PEP_BUILD_TESTS
TEST_CASE("engine") { printf("I am a test from the engine!\n"); }
#endif