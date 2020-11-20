#ifndef INC_05_GUESS_NUMBER_ASSETS_LOADER_H
#define INC_05_GUESS_NUMBER_ASSETS_LOADER_H

#include "game/game_func_load.h"

class AssetsLoader {
 public:
  explicit AssetsLoader(AssetsLoadingStrategy strategy);

  void LoadStaticAssets();

    [[nodiscard]] AssetsLoadingStrategy getAssetsLoadingStrategy() const;

    [[nodiscard]] const GameDescriptionInfo *getDescriptionInfo() const;

    [[nodiscard]] const std::unordered_map<Culture::Language, GameDescriptionStrings> *getDescriptionStrings() const;

    [[nodiscard]] const std::unordered_map<Culture::Language, std::vector<std::string>> *getStringAssets() const;

    [[nodiscard]] const std::vector<VariableDeclaration> *getGlobalVariableDeclarations() const;

    [[nodiscard]] const std::vector<Level> *getLevels() const;

    [[nodiscard]] Culture::Language getLanguage() const;

private:
  const AssetsLoadingStrategy _assets_loading_strategy{
      AssetsLoadingStrategy::kCompileTimeBuiltInAssets};

  const GameDescriptionInfo *_description_info;
  const std::unordered_map<Culture::Language, GameDescriptionStrings>
      *_description_strings;
  const std::unordered_map<Culture::Language, std::vector<std::string>>
      *_string_assets;
  const std::vector<VariableDeclaration> *_global_variable_declarations;
  const std::vector<Level> *_levels;
  Culture::Language _language;
};

#endif  // INC_05_GUESS_NUMBER_ASSETS_LOADER_H
