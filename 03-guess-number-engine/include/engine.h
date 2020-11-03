//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_ENGINE_H
#define INC_01_GUESS_NUMBER_PROTO_ENGINE_H

#include <memory>
#include <string>
#include <utility>

#include "assets_loader.h"
#include "game_level_logic_processor.h"
#include "game_variables_service.h"

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
