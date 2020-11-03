//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
#define INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H

#include <utils/engine_assets.h>

#include <memory>
#include <vector>

#include "game_variables.h"
#include "level.h"
#include "text_world_object_processor.h"

// TODO: factory
class GameLevelLogicProcessor {
 public:
  static void Init();
  static GameLevelLogicProcessor& GetSingleton();

  void ProcessLevel(size_t level_id);

  size_t getCurrentProcessingLevelId() const;

  void LoadTextWorldObject(size_t level_based_two_id);

 private:
  inline static std::unique_ptr<GameLevelLogicProcessor> singleton_;
  inline static bool is_inited;
  size_t current_processing_level_id_{};
};

#endif  // INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
