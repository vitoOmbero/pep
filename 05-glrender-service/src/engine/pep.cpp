//
// Created by vito on 31.10.20.
//
#include "engine/pep.h"

#include <cmath>
#include <random>

#include "engine/engine.h"
#include "engine/service/level_processing/game_level_logic_processor.h"

size_t GetUniformRandomNaturalNumber(size_t max) {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<size_t> uniform_dist(1, max);

  return uniform_dist(e1);
}

void pep::DoNothing() {
  // todo: how to do nothing?
}

void pep::LoadTextWorldObjectById(pep::index i) {
  GameLevelLogicProcessor::GetSingleton().LoadTextWorldObject(i);
}

void pep::LoadLevelById(pep::index i) {
  GameLevelLogicProcessor::GetSingleton().ProcessLevel(i);
}

size_t &pep::VarNatural(game_var_name name) {
  return GameVariablesService::global_vars.getVariableNatural(name);
}

bool &pep::VarBool(game_var_name name) {
  return GameVariablesService::global_vars.getVariableBool(name);
}

size_t pep::Log2FromNatural(game_var_name name) {
  auto &var = GameVariablesService::global_vars.getVariableNatural(name);
  return static_cast<size_t>(log2(static_cast<double>(var)));
}

size_t pep::NewRandomNatural(size_t max_value) {
  return GetUniformRandomNaturalNumber(max_value);
}

void pep::SetVarNaturalInterval(game_var_name interval, game_var_name natural_min, game_var_name natural_max) {
  auto& interval_ref = GameVariablesService::global_vars.getVariableNaturalInterval(interval);

  auto& min_ref = GameVariablesService::global_vars.getVariableNatural(natural_min);
  auto& max_ref = GameVariablesService::global_vars.getVariableNatural(natural_max);

  interval_ref = std::make_pair(min_ref, max_ref);
}
