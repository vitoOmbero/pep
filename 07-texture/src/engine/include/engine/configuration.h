#ifndef INC_05_GUESS_NUMBER_CONFIGURATION_H
#define INC_05_GUESS_NUMBER_CONFIGURATION_H

#include <unordered_map>
#include <vector>

#include "engine/assets_loading_startegy.h"
#include "engine/service/game_meta_info/game_description.h"
#include "engine_assets.h"
#include "engine/service/input_processing/keys.h"
#include "engine/service/glrenderer/texture_pack.h"

struct EngineConfiguration {
  const char *placeholder = "Some Engine Configuration";
};

struct GameConfiguration {
  const GameDescriptionInfo *DescriptionInfo;
  const std::unordered_map<Culture::Language, GameDescriptionStrings>
      *DescriptionStrings;
  const std::unordered_map<Culture::Language, std::vector<std::string>>
      *StringAssets;
  const std::vector<VariableDeclaration> *GlobalVariableDeclarations;
  const std::vector<Level> *Levels;
  Culture::Language Language;
  const InputModeVector * InputModes;
  const TexturePackMap * TexturePack;
};

inline EngineConfiguration gEngineConfiguration;
inline GameConfiguration gGameConfiguration;

#endif  // INC_05_GUESS_NUMBER_CONFIGURATION_H
