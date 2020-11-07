//
// Created by vito on 31.10.20.
//

#ifndef INC_03_GUESS_NUMBER_PEP_H
#define INC_03_GUESS_NUMBER_PEP_H

#include <string>

#include "engine/service/variable_processing/game_variables.h"

namespace pep {
using index = size_t;

void LoadTextWorldObjectById(index i);
void DoNothing();
void LoadLevelById(index i);
size_t &VarNatural(std::string name);
bool &VarBool(std::string name);
size_t Log2FromNatural(std::string name);
size_t NewRandomNatural(size_t max_value);

void SetVarNaturalInterval(game_var_name interval, game_var_name natural_min,
                           game_var_name natural_max);

}  // namespace pep

#endif  // INC_03_GUESS_NUMBER_PEP_H
