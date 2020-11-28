#ifndef GAME_LIBRARY_H
#define GAME_LIBRARY_H

#include "engine/configuration.h"
#include "symbol_export.h"

//#ifdef PEP_DL_TEST
namespace game {

PEP_DECLSPEC [[maybe_unused]] void hello_from_game();

}
//#endif

//#ifdef PEP_GAME_G_NUMBER

namespace game {

PEP_DECLSPEC [[maybe_unused]] const GameDescriptionInfo* getDescriptionInfo();
PEP_DECLSPEC [[maybe_unused]] const std::unordered_map<Culture::Language,
                                                       GameDescriptionStrings>*
getDescriptionStrings();

PEP_DECLSPEC
    [[maybe_unused]] const std::unordered_map<Culture::Language,
                                              std::vector<std::string>>*
    getStringAssets();
PEP_DECLSPEC [[maybe_unused]] const std::vector<VariableDeclaration>*
getGlobalVariableDeclarations();
PEP_DECLSPEC [[maybe_unused]] const std::vector<Level>* getLevels();
PEP_DECLSPEC [[maybe_unused]] Culture::Language getLanguage();
PEP_DECLSPEC [[maybe_unused]] AssetsLoadingStrategy getAssetsLoadingStrategy();
PEP_DECLSPEC [[maybe_unused]] InputModeVector* getInputModes();
PEP_DECLSPEC [[maybe_unused]] const TexturePackMap* getTexturePacks();
PEP_DECLSPEC [[maybe_unused]] const std::vector<SpriteMultiImage>*
getSpriteMultiImages();
}  // namespace game

//#endif

#endif  // GAME_LIBRARY_H
