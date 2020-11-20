//
// Created by vito on 29.10.20.
//

#include "g_number/logic.h"

#include "engine/pep.h"

void GuessNumber::Logic::intro_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::intro_level::Body() { pep::DoNothing(); }

void GuessNumber::Logic::intro_level::Transition() { pep::LoadLevelById(1); }

void GuessNumber::Logic::difficulty_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::difficulty_level::Body() { pep::DoNothing(); }

void GuessNumber::Logic::difficulty_level::Transition() {
  pep::LoadLevelById(2);
}

void GuessNumber::Logic::lobby_level::OnLoad() {
  using namespace pep;

  VarNatural("@secret_number") = NewRandomNatural(VarNatural("@number_max"));

  if (VarNatural("@difficulty_level") < 3) {
    VarNatural("@attempts_max") = Log2FromNatural("@secret_number");
    if (VarNatural("@difficulty_level") == 1) {
      LoadTextWorldObjectById(0);
    }
  } else {
    VarNatural("@attempts_max") = Log2FromNatural("@secret_number") / 3 * 2;
  }
}

void GuessNumber::Logic::lobby_level::Body() {
  using namespace pep;

  LoadTextWorldObjectById(1);
  LoadTextWorldObjectById(2);

#ifdef PEP_VERBOSE_GAME_LOGIC
  LoadTextWorldObjectById(3);
#endif
}

void GuessNumber::Logic::lobby_level::Transition() { pep::LoadLevelById(3); }

void GuessNumber::Logic::game_core_loop_level::OnLoad() {
  pep::VarBool("@finished") = false;
  pep::SetVarNaturalInterval("@num_interval", "@number_min", "@number_max");
}

void GuessNumber::Logic::game_core_loop_level::Body() {
  using namespace pep;

  while (!VarBool("@finished")) {
    LoadTextWorldObjectById(0);

    if (VarNatural("@effort_val") < VarNatural("@secret_number")) {
      LoadTextWorldObjectById(1);
      VarNatural("@attempt_counter") = VarNatural("@attempt_counter") + 1;
    }

    if (VarNatural("@effort_val") > VarNatural("@secret_number")) {
      LoadTextWorldObjectById(2);
      ++VarNatural("@attempt_counter");
    }

    if (VarNatural("@effort_val") == VarNatural("@secret_number")) {
      LoadTextWorldObjectById(3);
      VarBool("@finished") = true;
    }

    if (VarNatural("@attempt_counter") < VarNatural("@attempts_max")) {
      VarNatural("@attempts_left") =
          VarNatural("@attempts_max") - VarNatural("@attempt_counter");
      LoadTextWorldObjectById(4);
    } else {
      LoadTextWorldObjectById(5);
      VarBool("@finished") = true;
    }
  }
}

void GuessNumber::Logic::game_core_loop_level::Transition() {
  pep::LoadLevelById(4);
}

void GuessNumber::Logic::game_result_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void GuessNumber::Logic::game_result_level::Body() {
  using namespace pep;

  LoadTextWorldObjectById(1);
  LoadTextWorldObjectById(2);
  if (VarNatural("@attempt_counter") < VarNatural("@attempts_max")) {
    LoadTextWorldObjectById(3);
  } else {
    LoadTextWorldObjectById(4);
  }
}

void GuessNumber::Logic::game_result_level::Transition() { pep::DoNothing(); }
