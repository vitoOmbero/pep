#include "engine/pep.h"

#include <cmath>
#include <random>

#include "engine/engine_assets.h"
#include "engine/service/level_processing/game_level_logic_processor.h"
#include "engine/service/variable_processing/game_variables_service.h"

size_t pep::math::GetUniformRandomNaturalNumber(size_t max) {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<size_t> uniform_dist(1, max);

  return uniform_dist(e1);
}

void pep::LoadTextWorldObjectById(pep::index i) {
  GameLevelLogicProcessor::GetSingleton().LoadTextWorldObject(i);
}

void pep::DoNothing() {
  // NOTE: do nothing
}

void pep::LoadLevelById(pep::index i) {
  GameLevelLogicProcessor::GetSingleton().ProcessLevel(i);
}

size_t &pep::VarNatural(const std::string& name) {
  return GameVariablesService::global_vars.getVariableNatural(name);
}

bool &pep::VarBool(const std::string& name) {
  return GameVariablesService::global_vars.getVariableBool(name);
}

size_t pep::Log2FromNatural(const std::string& name) {
  auto& var = GameVariablesService::global_vars.getVariableNatural(name);
  return static_cast<size_t>(log2(static_cast<double>(var)));
}

size_t pep::NewRandomNatural(size_t max_value) {
  return math::GetUniformRandomNaturalNumber(max_value);
}

void pep::SetVarNaturalInterval(const game_var_name& interval, const game_var_name& natural_min, const game_var_name& natural_max) {
  auto& interval_ref =
          GameVariablesService::global_vars.getVariableNaturalInterval(interval);

  auto& min_ref =
          GameVariablesService::global_vars.getVariableNatural(natural_min);
  auto& max_ref =
          GameVariablesService::global_vars.getVariableNatural(natural_max);

  interval_ref = std::make_pair(min_ref, max_ref);
}
