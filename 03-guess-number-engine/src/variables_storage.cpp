//
// Created by vito on 31.10.20.
//

#include "variables_storage.h"

#include <algorithm>

#include "utils/terminal.h"

#ifdef PEP_VERBOSE_GAME_LOGIC
#define PEP_CHECK_MAP(MAP)               \
  if (MAP.find(name) == MAP.cend()) {    \
    Terminal::ReportErr(                 \
        ">> Bad usage of variable: not " \
        "found!");                       \
    Terminal::ReportErr("name:");        \
    Terminal::ReportErr(name);           \
    /*std::exit(EXIT_FAILURE);*/         \
  }
#endif

void VariablesStorage::Add(const std::vector<VariableDeclaration> &vds) {
  std::for_each(vds.begin(), vds.end(), [this](auto it) { AddVariable(it); });
}

void VariablesStorage::AddVariable(const VariableDeclaration &declaration) {
  switch (declaration.type) {
    case VariableType::kString:
      strings_[declaration.name] = ParseString(declaration);
      break;
    case VariableType::kChar:
      chars_[declaration.name] = ParseChar(declaration);
      break;
    case VariableType::kNatural0:
      naturals_[declaration.name] = ParseNatural0(declaration);
      break;
    case VariableType::kNatural:
      naturals_[declaration.name] = ParseNatural(declaration);
      break;
    case VariableType::kNaturalInterval:
      natural_intervals_[declaration.name] = ParseNaturalInterval(declaration);
      break;
    case VariableType::kBool:
      booleans_[declaration.name] = ParseBoolean(declaration);
      break;
  }
}

std::string &VariablesStorage::getVariableString(const game_var_name &name) {
#ifdef PEP_VERBOSE_GAME_LOGIC
  PEP_CHECK_MAP(strings_)
#endif
  return strings_[name];
}

size_t &VariablesStorage::getVariableNatural(const game_var_name &name) {
#ifdef PEP_VERBOSE_GAME_LOGIC
  PEP_CHECK_MAP(naturals_)
#endif
  return naturals_[name];
}

bool &VariablesStorage::getVariableBool(const game_var_name &name) {
#ifdef PEP_VERBOSE_GAME_LOGIC
  PEP_CHECK_MAP(booleans_)
#endif
  return booleans_[name];
}

char &VariablesStorage::getVariableChar(const game_var_name &name) {
#ifdef PEP_VERBOSE_GAME_LOGIC
  PEP_CHECK_MAP(chars_)
#endif
  return chars_[name];
}

std::pair<size_t, size_t> &VariablesStorage::getVariableNaturalInterval(
    const game_var_name &name) {
#ifdef PEP_VERBOSE_GAME_LOGIC
  PEP_CHECK_MAP(natural_intervals_)
#endif
  return natural_intervals_[name];
}
