//
// Created by vito on 2.11.20.
//

#include "engine/service/variable_processing/game_variables_service.h"

#include <algorithm>
#include <sstream>
#include <variant>

#include "game_guess_num_console_app/assets_loader.h"
#include "utils/terminal.h"

VariableType GameVariablesService::DefineType(game_var_name var) {
  auto it = std::find_if(Game::GlobalVariableDeclarations->cbegin(),
                         Game::GlobalVariableDeclarations->cend(),
                         [&var](auto it) { return it.name == var; });

#ifdef PEP_VERBOSE_GAME_LOGIC
  if (it == Game::GlobalVariableDeclarations->cend()) {
    Terminal::ReportErr(
        ">> Bad Variable usage: not found in game variable declarations!");
    Terminal::ReportErr("name: ");
    Terminal::ReportErr(var);
  }
#endif

  return it->type;
}

ValueTypeVariant GameVariablesService::GetValue(const game_var_name& name) {
  VariableType vt = GameVariablesService::DefineType(name);

  switch (vt) {
    case VariableType::kString: {
      return global_vars.getVariableString(name);
    } break;
    case VariableType::kChar: {
      return global_vars.getVariableChar(name);
    } break;
    case VariableType::kNatural0:
    case VariableType::kNatural: {
      return global_vars.getVariableNatural(name);
    } break;
    case VariableType::kNaturalInterval: {
      return global_vars.getVariableNaturalInterval(name);
    } break;
    case VariableType::kBool: {
      return global_vars.getVariableBool(name);
    } break;
    default: {
      Terminal::ReportErr("Dragons are spawned!");
      std::exit(EXIT_FAILURE);
    }
  }
}

std::string GameVariablesService::GetValueAsString(const game_var_name& name) {
  auto val = GetValue(name);

  switch (GameVariablesService::DefineType(name)) {
    case VariableType::kString:
      return std::string(std::get<std::string>(val));
    case VariableType::kChar:
      return std::string({std::get<char>(val)});
    case VariableType::kNatural0:
    case VariableType::kNatural:
      return std::to_string(std::get<std::size_t>(val));
    case VariableType::kNaturalInterval: {
      auto v = std::get<std::pair<size_t, size_t>>(val);
      std::ostringstream oss;
      oss << v.first << ".." << v.second;
      return oss.str();
    }
    case VariableType::kBool:
      return std::to_string(std::get<bool>(val));
    default: {
      Terminal::ReportErr("Dragons are spawned!");
      std::exit(EXIT_FAILURE);
    }
  }
}

VariablePtrTypeVariant GameVariablesService::GetVariableLValueReferencePointer(
    const game_var_name& name) {
  VariableType vt = GameVariablesService::DefineType(name);

  switch (vt) {
    case VariableType::kString:
      return &global_vars.getVariableString(name);
    case VariableType::kChar:
      return &global_vars.getVariableChar(name);
    case VariableType::kNatural0:
    case VariableType::kNatural:
      return &global_vars.getVariableNatural(name);
    case VariableType::kNaturalInterval:
      return &global_vars.getVariableNaturalInterval(name);
    case VariableType::kBool:
      return &global_vars.getVariableBool(name);
    default: {
      Terminal::ReportErr("Dragons are spawned!");
      std::exit(EXIT_FAILURE);
    }
  }
}