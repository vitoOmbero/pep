//
// Created by vito on 31.10.20.
//

#ifndef INC_03_GUESS_NUMBER_VARIABLES_STORAGE_H
#define INC_03_GUESS_NUMBER_VARIABLES_STORAGE_H

#include <cassert>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "game_variables.h"

// TODO: separate allocation
// TODO: system for managing local game level variables
// TODO: call to non-existing variable
// TODO: doubled declaration of variable
// TODO: another declaration with the same name case
class VariablesStorage {
 public:
  void Add(const std::vector<VariableDeclaration>& vds);

  void AddVariable(const VariableDeclaration& declaration);

  std::string& getVariableString(const game_var_name& name);
  size_t& getVariableNatural(const game_var_name& name);
  bool& getVariableBool(const game_var_name& name);
  char& getVariableChar(const game_var_name& name);
  std::pair<size_t, size_t>& getVariableNaturalInterval(const game_var_name& name);

 private:
  std::unordered_map<game_var_name, std::string> strings_;
  std::unordered_map<game_var_name, size_t> naturals_;
  std::unordered_map<game_var_name, bool> booleans_;
  std::unordered_map<game_var_name, char> chars_;
  std::unordered_map<game_var_name, std::pair<size_t, size_t>> natural_intervals_;
};
using ValueTypeVariant =
    std::variant<std::string, size_t, bool, char, std::pair<size_t, size_t>>;
// NOTE:: std::variant does not work with references
using VariablePtrTypeVariant = std::variant<std::string*, size_t*, bool*, char*,
                                            std::pair<size_t, size_t>*>;
#endif  // INC_03_GUESS_NUMBER_VARIABLES_STORAGE_H
