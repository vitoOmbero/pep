#include "engine/pep.h"

#include <cmath>
#include <random>

#include "engine/configuration.h"
#include "engine/engine_assets.h"
#include "engine/service/glrenderer/gl_renderer_service.h"
#include "engine/service/level_processing/game_level_logic_processor.h"
#include "engine/service/variable_processing/game_variables_service.h"
#include "service/input_processing/input_processing_service.h"
#include "utils/color_map.h"

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
  GameLevelLogicProcessor::GetSingleton().BreakMainLoop();
  GameLevelLogicProcessor::GetSingleton().SetNextLevel(i);
  GameLevelLogicProcessor::setTransition(true);
}

size_t& pep::VarNatural(const std::string& name) {
  return GameVariablesService::global_vars.getVariableNatural(name);
}

bool& pep::VarBool(const std::string& name) {
  return GameVariablesService::global_vars.getVariableBool(name);
}

size_t pep::Log2FromNatural(const std::string& name) {
  auto& var = GameVariablesService::global_vars.getVariableNatural(name);
  return static_cast<size_t>(log2(static_cast<double>(var)));
}

size_t pep::NewRandomNatural(size_t max_value) {
  return math::GetUniformRandomNaturalNumber(max_value);
}

void pep::SetVarNaturalInterval(const game_var_name& interval,
                                const game_var_name& natural_min,
                                const game_var_name& natural_max) {
  auto& interval_ref =
      GameVariablesService::global_vars.getVariableNaturalInterval(interval);

  auto& min_ref =
      GameVariablesService::global_vars.getVariableNatural(natural_min);
  auto& max_ref =
      GameVariablesService::global_vars.getVariableNatural(natural_max);

  interval_ref = std::make_pair(min_ref, max_ref);
}

size_t pep::GetCurrentLevelId() {
  return GameLevelLogicProcessor::GetSingleton().getCurrentProcessingLevelId();
}

void pep::EnableInputMode(pep::index input_mode_id) {
  InputProcessingService::EnableMode(input_mode_id);
}

void pep::LoadExitLevel() {
  GameLevelLogicProcessor::GetSingleton().BreakMainLoop();
  GameLevelLogicProcessor::GetSingleton().SetNextLevel(gGameConfiguration.DescriptionInfo->exit_point);
  GameLevelLogicProcessor::setTransition(false);
}

void pep::render::SwitchGlPolygonMode(GlPolygonMode gl_polygon_mode) {
  GlRendererService::SwitchGlPolygonMode(gl_polygon_mode);
}

void pep::render::SetClearColorName(ColorMap::Color name) {
  SetClearColorRgb888(ColorMap::FindRgbCode(name));
}

void pep::render::SetClearColorRgb888(ColorMap::Rgb888 rgb) {
  GLclampf r = rgb.r / 255.;
  GLclampf g = rgb.g / 255.;
  GLclampf b = rgb.b / 255.;
  gl_color c{r, g, b, 1.};
  GlRendererService::SetGlClearColor(c);
}

ColorMap::Color pep::render::FindColor(ColorMap::Rgb888 rgb) {
  return ColorMap::FindColor(rgb);
}

ColorMap::Rgb888 pep::render::FindRgbCode(ColorMap::Color colorName) {
  return ColorMap::FindRgbCode(colorName);
}

ColorMap::Color pep::render::FindClosestColor(ColorMap::Rgb888 rgb) {
  return ColorMap::FindClosestColor(rgb);
}

ColorMap::Rgb888 pep::render::GetClearColor() {
  gl_color c = GlRendererService::GetGlClearColor();
  uchar r = c.red * 255;
  uchar g = c.green * 255;
  uchar b = c.blue * 255;
  return {r, g, b};
}
