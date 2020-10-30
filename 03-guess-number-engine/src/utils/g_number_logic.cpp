//
// Created by vito on 29.10.20.
//

#include "utils/g_number_logic.h"

#include "game_level_logic_processor.h"

using gllp = GameLevelLogicProcessor;

void GuessNumber::Logic::intro_level::OnLoad() {
  gllp::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::intro_level::Body() { gllp::DoNothing(); }

void GuessNumber::Logic::intro_level::Transition() { gllp::LoadLevelById(1); }

void GuessNumber::Logic::difficulty_level::OnLoad() {
  gllp::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::difficulty_level::Body() { gllp::DoNothing(); }

void GuessNumber::Logic::difficulty_level::Transition() {
  gllp::LoadLevelById(2);
}

void GuessNumber::Logic::lobby_level::OnLoad() {
  if (gllp::VarNatural("@difficulty_level") < 3) {
    gllp::VarNatural("@attempts_max") = gllp::Log2FromNatural("@secret_number");
    if (gllp::VarNatural("@difficulty_level") == 1) {
      gllp::LoadTextWorldObjectById(0);
    }
  } else {
    gllp::VarNatural("@attempts_max") =
        gllp::Log2FromNatural("@secret_number") / 3 * 2;
  }
}

void GuessNumber::Logic::lobby_level::Body() {
  gllp::LoadTextWorldObjectById(1);
  gllp::LoadTextWorldObjectById(2);

  gllp::VarNatural("@secret_number") =
      gllp::NewRandomNatural(gllp::VarNatural("@number_max"));

#ifdef PEP_VERBOSE_GAME_LOGIC
  gllp::LoadTextWorldObjectById(3);
#endif
}

void GuessNumber::Logic::lobby_level::Transition() { gllp::LoadLevelById(3); }

void GuessNumber::Logic::game_core_loop_level::OnLoad() {
  gllp::VarBool("@finished") = false;
}

void GuessNumber::Logic::game_core_loop_level::Body() {
  while (!gllp::VarBool("@finished")) {
    gllp::LoadTextWorldObjectById(0);

    if (gllp::VarNatural("@effort_val") < gllp::VarNatural("@secret_number")) {
      gllp::LoadTextWorldObjectById(1);
      ++gllp::VarNatural("@attempt_counter");
    }

    if (gllp::VarNatural("@effort_val") > gllp::VarNatural("@secret_number")) {
      gllp::LoadTextWorldObjectById(2);
      ++gllp::VarNatural("@attempt_counter");
    }

    if (gllp::VarNatural("@effort_val") == gllp::VarNatural("@secret_number")) {
      gllp::LoadTextWorldObjectById(3);
      gllp::VarBool("@finished") = true;
    }

    if (gllp::VarNatural("@attempt_counter") <
        gllp::VarNatural("@attempts_max")) {
      gllp::LoadTextWorldObjectById(4);
    } else {
      gllp::LoadTextWorldObjectById(5);
      gllp::VarBool("@finished") = true;
    }
  }
}

void GuessNumber::Logic::game_core_loop_level::Transition() {
  gllp::LoadLevelById(4);
}

void GuessNumber::Logic::game_result_level::OnLoad() {
  gllp::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::game_result_level::Body() {
  gllp::LoadTextWorldObjectById(1);
  gllp::LoadTextWorldObjectById(2);
  if (gllp::VarNatural("@attempt_counter") <
      gllp::VarNatural("@attempts_max")) {
    gllp::LoadTextWorldObjectById(3);
  } else {
    gllp::LoadTextWorldObjectById(4);
  }
}

void GuessNumber::Logic::game_result_level::Transition() { gllp::DoNothing(); }
