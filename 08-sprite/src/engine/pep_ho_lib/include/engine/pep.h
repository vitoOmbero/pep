#ifndef PEP_ENGINE_LIB_H
#define PEP_ENGINE_LIB_H

#include <cstddef>
#include <cstdint>
#include <string>

#include "engine/engine_assets.h"
#include "engine/service/glrenderer/game_objects.h"
#include "engine/service/glrenderer/gl_types.h"
#include "engine/service/input_processing/keys.h"
#include "engine/service/level_processing/level.h"
#include "engine/service/text_world/game_objects.h"
#include "engine/service/variable_processing/game_variables.h"
#include "engine/utils/color.h"
#include "engine/utils/rgb888.h"
#include "engine/service/glrenderer/texture_pack.h"
#include "engine/service/game_update/sprite_multi_image.h"

namespace pep {

namespace math {
size_t GetUniformRandomNaturalNumber(size_t max);
}  // namespace math

namespace render {
void SwitchGlPolygonMode(GlPolygonMode gl_polygon_mode);
void SetClearColorName(ColorMap::Color name);
void SetClearColorRgb888(ColorMap::Rgb888 rgb);
ColorMap::Rgb888 GetClearColor();
ColorMap::Color FindColor(ColorMap::Rgb888 rgb);
ColorMap::Rgb888 FindRgbCode(ColorMap::Color colorName);
ColorMap::Color FindClosestColor(ColorMap::Rgb888 rgb);

}  // namespace render

using index = size_t;

void LoadTextWorldObjectById(index i);
void DoNothing();
void LoadLevelById(index i);
size_t& VarNatural(const std::string& name);
bool& VarBool(const std::string& name);
size_t Log2FromNatural(const std::string& name);

size_t NewRandomNatural(size_t max_value);

void SetVarNaturalInterval(const game_var_name& interval,
                           const game_var_name& natural_min,
                           const game_var_name& natural_max);

size_t GetCurrentLevelId();

void EnableInputMode(index input_mode_id);

void LoadExitLevel();

}  // namespace pep
#endif