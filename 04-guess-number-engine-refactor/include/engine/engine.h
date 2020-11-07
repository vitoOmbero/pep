//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_ENGINE_H
#define INC_01_GUESS_NUMBER_PROTO_ENGINE_H

#include <memory>
#include <string>
#include <utility>

#include "game_guess_num_console_app/assets_loader.h"
#include "engine/service/level_processing/game_level_logic_processor.h"
#include "engine/service/variable_processing/game_variables_service.h"

namespace pep {

void AtExitMessage();

class Engine {
 public:
  friend void AtExitMessage();

  Engine();

  void Play();

 private:
  inline static std::string at_exit_message{""};
  inline static bool is_inited{false};
  inline static Engine* singleton_{nullptr};
};

}  // namespace pep
#endif  // INC_01_GUESS_NUMBER_PROTO_ENGINE_H
