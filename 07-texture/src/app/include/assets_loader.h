#ifndef INC_05_GUESS_NUMBER_ASSETS_LOADER_H
#define INC_05_GUESS_NUMBER_ASSETS_LOADER_H

#include "game/game_func_load.h"

class AssetsLoader {
 public:
  explicit AssetsLoader(AssetsLoadingStrategy strategy);

  void LoadStaticAssets();

  [[nodiscard]] AssetsLoadingStrategy getAssetsLoadingStrategy() const;

  [[nodiscard]] const GameDescriptionInfo *getDescriptionInfo() const;

  [[nodiscard]] const std::unordered_map<Culture::Language,
                                         GameDescriptionStrings>
      *getDescriptionStrings() const;

  [[nodiscard]] const std::unordered_map<Culture::Language,
                                         std::vector<std::string>>
      *getStringAssets() const;

  [[nodiscard]] const std::vector<VariableDeclaration>
      *getGlobalVariableDeclarations() const;

  [[nodiscard]] const std::vector<Level> *getLevels() const;

  [[nodiscard]] Culture::Language getLanguage() const;

  [[nodiscard]] const InputModeVector *getInputModes() const;

  [[nodiscard]] const TexturePackMap *getTexturePackMap() const;

 private:
  const AssetsLoadingStrategy _assets_loading_strategy{
      AssetsLoadingStrategy::kCompileTimeBuiltInAssets};

  const GameDescriptionInfo *description_info_;
  const std::unordered_map<Culture::Language, GameDescriptionStrings>
      *description_strings_;
  const std::unordered_map<Culture::Language, std::vector<std::string>>
      *string_assets_;
  const std::vector<VariableDeclaration> *global_variable_declarations_;
  const std::vector<Level> *levels_;
  const InputModeVector *input_modes_;
  const TexturePackMap *texture_pack_map_;
  Culture::Language language_;
};

#endif  // INC_05_GUESS_NUMBER_ASSETS_LOADER_H
