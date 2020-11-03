//
// Created by vito on 2.11.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_VARIABLES_SERVICE_H
#define INC_03_GUESS_NUMBER_GAME_VARIABLES_SERVICE_H

#include "variables_storage.h"

class GameVariablesService {
 public:
  inline static VariablesStorage global_vars;

  static VariableType DefineType(game_var_name var);

  static VariablePtrTypeVariant GetVariableLValueReferencePointer(
      const game_var_name &name);

  static ValueTypeVariant GetValue(const game_var_name &name);

  static std::string GetValueAsString(const game_var_name &name);
};

#endif  // INC_03_GUESS_NUMBER_GAME_VARIABLES_SERVICE_H
