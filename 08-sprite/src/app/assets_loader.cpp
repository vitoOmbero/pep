#include "assets_loader.h"

#include <cassert>

#include "fpc.h"

AssetsLoader::AssetsLoader(AssetsLoadingStrategy strategy) {
  // TODO: add assert loading from files
  assert(strategy == _assets_loading_strategy);
}

void AssetsLoader::LoadStaticAssets() {
  auto fpc = game_fpc::Get();
  description_info_ = fpc.GetDescriptionInfo();
  description_strings_ = fpc.GetDescriptionStrings();
  string_assets_ = fpc.GetStringAssets();
  global_variable_declarations_ = fpc.GetGlobalVariableDeclarations();
  levels_ = fpc.GetLevels();
  language_ = fpc.GetLanguage();
  input_modes_ = fpc.GetInputModes();
  texture_pack_map_ = fpc.GetTexturePacks();
  sprite_multi_images_ = fpc.GetSpriteMultiImages();

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
  return description_info_;
}

const std::unordered_map<Culture::Language, GameDescriptionStrings>
    *AssetsLoader::getDescriptionStrings() const {
  return description_strings_;
}

const std::unordered_map<Culture::Language, std::vector<std::string>>
    *AssetsLoader::getStringAssets() const {
  return string_assets_;
}

const std::vector<VariableDeclaration>
    *AssetsLoader::getGlobalVariableDeclarations() const {
  return global_variable_declarations_;
}

const std::vector<Level> *AssetsLoader::getLevels() const { return levels_; }

Culture::Language AssetsLoader::getLanguage() const { return language_; }

const InputModeVector *AssetsLoader::getInputModes() const {
  return input_modes_;
}

const TexturePackMap *AssetsLoader::getTexturePackMap() const {
  return texture_pack_map_;
}

const std::vector<SpriteMultiImage> *AssetsLoader::getSpriteMultiImages() const {
  return sprite_multi_images_;
}
