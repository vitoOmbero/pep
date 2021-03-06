//
// Created by vito on 1.11.20.
//

#ifndef INC_03_GUESS_NUMBER_TEXT_WORLD_OBJECT_PROCESSOR_H
#define INC_03_GUESS_NUMBER_TEXT_WORLD_OBJECT_PROCESSOR_H

#include <unordered_map>

#include "game_objects.h"
#include "game_variables.h"
#include "utils/engine_assets.h"

/**
 * Current realisation works with Terminal only
 */
class TextWorldObjectProcessor {
 public:
  explicit TextWorldObjectProcessor(size_t current_level_id);
  void Process(text_world_objects::Type two);

 private:
  size_t current_level_id_;

};  // namespace TextWorldObjectProcessor

#endif  // INC_03_GUESS_NUMBER_TEXT_WORLD_OBJECT_PROCESSOR_H
