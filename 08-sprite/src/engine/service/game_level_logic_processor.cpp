#include "engine/service/level_processing/game_level_logic_processor.h"

#include <chrono>
#include <thread>

#include "engine/configuration.h"
#include "service/event_processing/event_processing_service.h"
#include "service/game_update/game_update_service.h"
#include "service/glrenderer/gl_renderer.h"
#include "service/glrenderer/gl_renderer_service.h"
#include "service/glrenderer/mesh.h"
#include "service/text_world/game_objects.h"
#include "utils/file_to_string.h"
#include "utils/terminal.h"

void GameLevelLogicProcessor::ProcessLevel(size_t level_id) {
  current_processing_level_id_ = level_id;
  (*gGameConfiguration.Levels)[level_id].game_logic.OnLoad();

  is_continuing_ = true;

  auto timer = std::chrono::high_resolution_clock();
  auto begin = timer.now();

  GlRendererService::InitFor(level_id);

  while (is_continuing_) {
    auto last_frame_end = timer.now();

    EventProcessingService::ProcessEvent();

    frame_delta_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        last_frame_end - begin);

    if (frame_delta_.count() < 1000 % 60) {
      std::this_thread::yield();
      continue;
    }

    GameUpdateService::Update(frame_delta_);

    GlRendererService::Render();

    (*gGameConfiguration.Levels)[level_id].game_logic.ExecuteTextWorldLogic();

    (*gGameConfiguration.Levels)[level_id].game_logic.Transition();

    begin = last_frame_end;
  }

  GlRendererService::Destroy();
}

size_t GameLevelLogicProcessor::getCurrentProcessingLevelId() const {
  return current_processing_level_id_;
}

void GameLevelLogicProcessor::Init() {
  if (!is_inited_) {
    singleton_ = std::make_unique<GameLevelLogicProcessor>();
    is_inited_ = true;
  }
#ifdef PEP_VERBOSE_GAME_LOGIC
  else
    Terminal::ReportErr("Bad usage of GameLevelLogicProcessor singleton!");
#endif
}

GameLevelLogicProcessor &GameLevelLogicProcessor::GetSingleton() {
  if (is_inited_) {
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

void GameLevelLogicProcessor::LoadTextWorldObject(
    size_t level_based_two_id) const {
  auto two = (*gGameConfiguration.Levels)[current_processing_level_id_]
                 .text_world_objects[level_based_two_id];
  // TODO: checks for AssetsLoader
  TextWorldObjectProcessor(current_processing_level_id_).Process(two);
}

void GameLevelLogicProcessor::BreakMainLoop() { is_continuing_ = false; }

void GameLevelLogicProcessor::SetNextLevel(size_t i) {
  next_processing_level_id = i;
}

bool GameLevelLogicProcessor::isNotLastLevel() { return is_transition_; }

void GameLevelLogicProcessor::ProcessNextLevel() {
  is_transition_ = false;
  current_processing_level_id_ = next_processing_level_id;
  ProcessLevel(current_processing_level_id_);
}

void GameLevelLogicProcessor::setNotLastLevel(bool b) { is_transition_ = b; }
