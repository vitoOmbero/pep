#include "assets_loader.h"

#include <cassert>

#include "fpc.h"

AssetsLoader::AssetsLoader(AssetsLoadingStrategy strategy) {
  // TODO: add assert loading from files
  assert(strategy == _assets_loading_strategy);
}

void AssetsLoader::LoadStaticAssets() {
  auto fpc = game_fpc::Get();
  _description_info = fpc.GetDescriptionInfo();
  _description_strings = fpc.GetDescriptionStrings();
  _string_assets = fpc.GetStringAssets();
  _global_variable_declarations = fpc.GetGlobalVariableDeclarations();
  _levels = fpc.GetLevels();
  _language = fpc.GetLanguage();
  _input_modes = fpc.GetInputModes();

#ifdef  PEP_DEBUG
  std::cout << fpc.GetDescriptionInfo()->project_work_name << std::endl;
  std::cout << "Levels:" << std::endl;
  std::cout << fpc.GetLevels()->size() << std::endl;
  std::cout << "Variables:" << std::endl;
  std::cout << fpc.GetGlobalVariableDeclarations()->size() << std::endl;
  std::cout << "First Var name:" << std::endl;
  std::cout << fpc.GetGlobalVariableDeclarations()->at(0).name;
#endif

}

AssetsLoadingStrategy AssetsLoader::getAssetsLoadingStrategy() const {
  return _assets_loading_strategy;
}

const GameDescriptionInfo *AssetsLoader::getDescriptionInfo() const {
  return _description_info;
}

const std::unordered_map<Culture::Language, GameDescriptionStrings>
    *AssetsLoader::getDescriptionStrings() const {
  return _description_strings;
}

const std::unordered_map<Culture::Language, std::vector<std::string>>
    *AssetsLoader::getStringAssets() const {
  return _string_assets;
}

const std::vector<VariableDeclaration>
    *AssetsLoader::getGlobalVariableDeclarations() const {
  return _global_variable_declarations;
}

const std::vector<Level> *AssetsLoader::getLevels() const { return _levels; }

Culture::Language AssetsLoader::getLanguage() const { return _language; }

const InputModeVector *AssetsLoader::getInputModes() const {
  return _input_modes;
}
