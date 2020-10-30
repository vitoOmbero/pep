//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_VARIABLES_H
#define INC_03_GUESS_NUMBER_GAME_VARIABLES_H

#include <string>
#include <variant>
#include <vector>

using game_var_t = std::string;

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
  game_var_t name;
};

struct VariableAssignation {
  game_var_t name;
  std::string value;
};

namespace Input {
struct NonNegativeInteger {
  size_t max;
  size_t min = 1;
};

struct AsciiCharInput {
  std::vector<char> allowed;
};

using Type = std::variant<NonNegativeInteger, AsciiCharInput>;
};  // namespace Input

#endif  // INC_03_GUESS_NUMBER_GAME_VARIABLES_H
