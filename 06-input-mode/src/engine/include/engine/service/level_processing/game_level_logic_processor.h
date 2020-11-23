//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
#define INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H

#include <engine/engine_assets.h>

#include <chrono>
#include <memory>
#include <vector>

#include "engine/service/variable_processing/game_variables.h"
#include "level.h"
#include "engine/service/text_world/text_world_object_processor.h"

// TODO: factory
class GameLevelLogicProcessor {
 public:
  static void Init();
  static GameLevelLogicProcessor& GetSingleton();

  void ProcessLevel(size_t level_id);

  size_t getCurrentProcessingLevelId() const;

  void LoadTextWorldObject(size_t level_based_two_id) const;

  static void BreakMainLoop();

 private:
  inline static std::unique_ptr<GameLevelLogicProcessor> singleton_;
  inline static bool is_inited_;
  inline static bool is_continuing_;
  size_t current_processing_level_id_{};
  std::chrono::milliseconds frame_delta_;
};

#endif  // INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
