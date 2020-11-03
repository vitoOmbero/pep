//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_VARIABLES_H
#define INC_03_GUESS_NUMBER_GAME_VARIABLES_H

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "utils/terminal.h"

using game_var_name = std::string;

enum class VariableType {
  kString,
  kChar,
  kNatural0,
  kNatural,
  kNaturalInterval,
  kBool,
};

struct VariableDeclaration {
  VariableType type;
  game_var_name name;
  std::string value;
};

namespace Input {
struct NonNegativeInteger {
  size_t max{10};
  size_t min{1};
};

struct AsciiCharInput {
  std::vector<char> allowed;
};

using Type = std::variant<NonNegativeInteger, AsciiCharInput, std::monostate>;
};  // namespace Input

// TODO: add checks
inline size_t ParseNatural0(const VariableDeclaration& declaration) {
  if (declaration.value.empty()) return 0;

  size_t val = static_cast<size_t>(std::stoul(declaration.value));
  if (val == 0) {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(">> Bad Natural0 initialisation:");
    Terminal::ReportErr("name : ");
    Terminal::ReportErr(declaration.name);
#endif
    val = 1;
  }
  return val;
}
// TODO: add checks
inline size_t ParseNatural(const VariableDeclaration& declaration) {
  if (declaration.value.empty()) return 0;
  return static_cast<size_t>(std::stoul(declaration.value));
}
// TODO: add checks
inline char ParseChar(const VariableDeclaration& declaration) {
  if (declaration.value.empty()) {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(">> Bad Char initialisation:");
    Terminal::ReportErr("name : ");
    Terminal::ReportErr(declaration.name);
#endif
    return '?';
  }
  return declaration.value[0];
}
// TODO: add checks
inline std::string ParseString(const VariableDeclaration& declaration) {
  if (declaration.name.empty()) {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(">> Bad String initialisation:");
    Terminal::ReportErr("name : ");
    Terminal::ReportErr(declaration.name);
#endif
    return "<empty string>";
  }
  return declaration.value;
}

// TODO: add checks
inline std::pair<size_t, size_t> ParseNaturalInterval(
    const VariableDeclaration& declaration) {
  if (declaration.value.empty()) {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(">> Bad NaturalInterval initialisation:");
    Terminal::ReportErr("name : ");
    Terminal::ReportErr(declaration.name);
#endif
    return std::make_pair(0, 1);
  }

  auto separator = declaration.value.find_first_of('-');

  return std::make_pair<size_t, size_t>(
      static_cast<size_t>(std::stoul(declaration.value.substr(0, separator))),
      static_cast<size_t>(std::stoul(declaration.value.substr(
          separator + 1, declaration.value.size() - separator))));
}

// TODO: add checks
inline bool ParseBoolean(const VariableDeclaration& declaration) {
  if (declaration.value.empty()) return false;
  if (declaration.value.size() > 1) {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(">> Bad Boolean initialisation:");
    Terminal::ReportErr("name : ");
    Terminal::ReportErr(declaration.name);
#endif
    return false;
  }
  return (declaration.value[0] == '+');
}

#endif  // INC_03_GUESS_NUMBER_GAME_VARIABLES_H
