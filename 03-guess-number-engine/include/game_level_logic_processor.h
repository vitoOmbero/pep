//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
#define INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H

#include <stddef.h>

#include "game_variables.h"

struct GameLevelLogic {
  using callback_t = void (*)();

  callback_t OnLoad;
  callback_t Body;
  callback_t Transition;
};

class GameLevelLogicProcessor {
 public:
  using index = size_t;

  static void LoadTextWorldObjectById(index i);

  static void DoNothing();

  static void LoadLevelById(index i);

  static size_t &VarNatural(game_var_t name);
  static bool &VarBool(game_var_t name);

  static size_t &Log2FromNatural(game_var_t name);

  static size_t &NewRandomNatural(size_t max_value);
};

#endif  // INC_03_GUESS_NUMBER_GAME_LEVEL_LOGIC_PROCESSOR_H
