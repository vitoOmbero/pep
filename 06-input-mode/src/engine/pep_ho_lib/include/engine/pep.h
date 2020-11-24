#ifndef PEP_ENGINE_LIB_H
#define PEP_ENGINE_LIB_H

#include <cstddef>
#include <cstdint>
#include <string>

#include "engine/engine_assets.h"
#include "engine/service/variable_processing/game_variables.h"
#include "engine/service/text_world/game_objects.h"
#include "engine/service/glrenderer/game_objects.h"
#include "engine/service/level_processing/level.h"

namespace pep {

namespace math {
size_t GetUniformRandomNaturalNumber(size_t max);
}  // namespace math

using index = size_t;

void LoadTextWorldObjectById(index i);
void DoNothing();
void LoadLevelById(index i);
size_t& VarNatural(const std::string& name);
bool& VarBool(const std::string& name);
size_t Log2FromNatural(const std::string& name);

size_t NewRandomNatural(size_t max_value);

void SetVarNaturalInterval(const game_var_name& interval, const game_var_name& natural_min,
                           const game_var_name& natural_max);

}  // namespace pep
#endif