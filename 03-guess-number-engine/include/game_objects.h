//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_OBJECTS_H
#define INC_03_GUESS_NUMBER_GAME_OBJECTS_H

#include <variant>
#include <vector>

#include "game_variables.h"

namespace text_world_objects {
struct DialogNaturalInput {
  game_var_name input_result;
  size_t msg_tip_index = 0;
  size_t msg_bad_index = 1;
  bool is_using_templated_messages = true;
  game_var_name natural_interval_display = "";
};

struct Stand {
  enum class Layout {
    kFixedDefaultBordered,
    kPureText,
  };

  std::vector<game_var_name> args_to_show;
  bool is_input_expected = true;
  Layout layout = Layout::kFixedDefaultBordered;
  size_t msg_index = 0;
};

/*
 * Menu
 * Options
 * Table
 */

using Type = std::variant<DialogNaturalInput, Stand, std::monostate>;
}  // namespace text_world_objects

#endif  // INC_03_GUESS_NUMBER_GAME_OBJECTS_H
