#ifndef GAME_LOAD_LIB_LOAD_H
#define GAME_LOAD_LIB_LOAD_H

#include <dlfcn.h>

#include <cstddef>
#include <cstdint>
#include <iostream>

#include "libgame.h"

namespace game_func_load::ptrs {
using PrintHelloFromGame = void (*)();
using GetDescriptionInfo = const GameDescriptionInfo* (*)();
using GetDescriptionStrings =
    const std::unordered_map<Culture::Language, GameDescriptionStrings>* (*)();
using GetStringAssets = const std::unordered_map<
    Culture::Language, std::vector<std::string>>* (*)();
using GetGlobalVariableDeclarations =
    const std::vector<VariableDeclaration>* (*)();
using GetLevels = const std::vector<Level>* (*)();
using GetLanguage = Culture::Language (*)();
using GetAssetsLoadingStrategy = AssetsLoadingStrategy (*)();
using GetInputModes = InputModeVector* (*)();
using GetTexturePacks = const TexturePackMap* (*)();
using GetSpriteMultiImages = const std::vector<SpriteMultiImage>* (*)();
}  // namespace game_func_load::ptrs

#ifndef PTRS_ONLY
namespace game_func_load::symbols {
static const char* PrintHelloFromGame = "hello_from_game";
static const char* GetDescriptionInfo = "getDescriptionInfo";
static const char* GetDescriptionStrings = "getDescriptionStrings";
static const char* GetStringAssets = "getStringAssets";
static const char* GetGlobalVariableDeclarations =
    "getGlobalVariableDeclarations";
static const char* GetLevels = "getLevels";
static const char* GetLanguage = "getLanguage";
static const char* GetAssetsLoadingStrategy = "getAssetsLoadingStrategy";
static const char* GetInputModes = "getInputModes";
static const char* GetTexturePacks = "getTexturePacks";
static const char* GetSpriteMultiImages = "getSpriteMultiImages";
}  // namespace game_func_load::symbols
#endif

inline static const char* lib_game_name{"libgame.so"};
inline static void* game_handle;

struct game_loaded_ptrs {
  game_func_load::ptrs::PrintHelloFromGame PrintHelloFromGame;
  game_func_load::ptrs::GetDescriptionInfo GetDescriptionInfo;
  game_func_load::ptrs::GetDescriptionStrings GetDescriptionStrings;
  game_func_load::ptrs::GetStringAssets GetStringAssets;
  game_func_load::ptrs::GetGlobalVariableDeclarations
      GetGlobalVariableDeclarations;
  game_func_load::ptrs::GetLevels GetLevels;
  game_func_load::ptrs::GetLanguage GetLanguage;
  game_func_load::ptrs::GetAssetsLoadingStrategy GetAssetsLoadingStrategy;
  game_func_load::ptrs::GetInputModes GetInputModes;
  game_func_load::ptrs::GetTexturePacks GetTexturePacks;
  game_func_load::ptrs::GetSpriteMultiImages GetSpriteMultiImages;
};

inline static void LoadFunctions(game_loaded_ptrs& fpc /*out*/) {
  using namespace game_func_load;

  game_handle = dlopen(lib_game_name, RTLD_LAZY);

  if (nullptr == game_handle) {
    std::cerr << dlerror() << std::endl;
    std::terminate();
  }

  fpc.PrintHelloFromGame =
      (ptrs::PrintHelloFromGame)dlsym(game_handle, symbols::PrintHelloFromGame);
  fpc.GetDescriptionInfo =
      (ptrs::GetDescriptionInfo)dlsym(game_handle, symbols::GetDescriptionInfo);
  fpc.GetDescriptionStrings = (ptrs::GetDescriptionStrings)dlsym(
      game_handle, symbols::GetDescriptionStrings);
  fpc.GetStringAssets =
      (ptrs::GetStringAssets)dlsym(game_handle, symbols::GetStringAssets);
  fpc.GetGlobalVariableDeclarations =
      (ptrs::GetGlobalVariableDeclarations)dlsym(
          game_handle, symbols::GetGlobalVariableDeclarations);
  fpc.GetLevels = (ptrs::GetLevels)dlsym(game_handle, symbols::GetLevels);
  fpc.GetLanguage = (ptrs::GetLanguage)dlsym(game_handle, symbols::GetLanguage);
  fpc.GetAssetsLoadingStrategy = (ptrs::GetAssetsLoadingStrategy)dlsym(
      game_handle, symbols::GetAssetsLoadingStrategy);
  fpc.GetInputModes =
      (ptrs::GetInputModes)dlsym(game_handle, symbols::GetInputModes);
  fpc.GetTexturePacks =
      (ptrs::GetTexturePacks)dlsym(game_handle, symbols::GetTexturePacks);
  fpc.GetSpriteMultiImages = (ptrs::GetSpriteMultiImages)dlsym(
      game_handle, symbols::GetSpriteMultiImages);
}

#endif