//
// Created by vito on 30.10.20.
//

#include "engine/service/level_processing/game_level_logic_processor.h"

#include "engine/configuration.h"

#include "engine/service/text_world/game_objects.h"
#include "utils/terminal.h"

void GameLevelLogicProcessor::ProcessLevel(size_t level_id) {
  current_processing_level_id_ = level_id;
  (*gGameConfiguration.Levels)[level_id].game_logic.OnLoad();
  (*gGameConfiguration.Levels)[level_id].game_logic.Body();
  (*gGameConfiguration.Levels)[level_id].game_logic.Transition();
}

size_t GameLevelLogicProcessor::getCurrentProcessingLevelId() const {
  return current_processing_level_id_;
}

void GameLevelLogicProcessor::Init() {
  if (!is_inited) {
    singleton_ = std::make_unique<GameLevelLogicProcessor>();
    is_inited = true;
  }
#ifdef PEP_VERBOSE_GAME_LOGIC
  else
    Terminal::ReportErr("Bad usage of GameLevelLogicProcessor singleton!");
#endif
}

GameLevelLogicProcessor &GameLevelLogicProcessor::GetSingleton() {
  if (is_inited) {
    return *singleton_;
  } else {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(
        "GameLevelLogicProcessor singleton is not created yet!");
    Terminal::ReportErr("It is very, very bad!");
#endif
    std::exit(EXIT_FAILURE);
  }
}

void GameLevelLogicProcessor::LoadTextWorldObject(size_t level_based_two_id) const {
  auto two = (*gGameConfiguration.Levels)[current_processing_level_id_]
                 .text_world_objects[level_based_two_id];
  // TODO: checks for AssetsLoader
  TextWorldObjectProcessor(current_processing_level_id_).Process(two);
}
