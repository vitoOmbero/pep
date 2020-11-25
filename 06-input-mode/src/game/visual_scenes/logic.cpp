#include "visual_scenes/logic.h"

#include "engine/pep.h"

void VisualScenes::Logic::intro_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void VisualScenes::Logic::intro_level::ExecuteTextWorldLogic() {
  pep::DoNothing();
}

void VisualScenes::Logic::intro_level::Transition() { pep::LoadLevelById(1); }

static void PrintTips() {
  pep::LoadTextWorldObjectById(1);
  pep::LoadTextWorldObjectById(2);
  pep::LoadTextWorldObjectById(3);
  pep::LoadTextWorldObjectById(4);
  pep::LoadTextWorldObjectById(5);
}

void VisualScenes::Logic::triangle_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
  pep::EnableInputMode(0);
  PrintTips();
}

void VisualScenes::Logic::triangle_level::ExecuteTextWorldLogic() {
  pep::DoNothing();
}

void VisualScenes::Logic::triangle_level::
    Transition() { /*level transition is managed by game logic*/
}

void VisualScenes::Logic::quad_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
  pep::EnableInputMode(0);
  PrintTips();
}

void VisualScenes::Logic::quad_level::ExecuteTextWorldLogic() {
  pep::DoNothing();
}

void VisualScenes::Logic::quad_level::Transition() { /*level transition is
                                                        managed by game logic*/
}

void VisualScenes::Logic::Input::SwitchPolygonMode() {
#ifdef PEP_VERBOSE_GAME_LOGIC
  Terminal::ReportMsg("SwitchPolygonMode is called...");
#endif

  static bool flag;

  flag = !flag;

  if (flag) {
    pep::render::SwitchGlPolygonMode(GlPolygonMode::kGlLine);
  } else {
    pep::render::SwitchGlPolygonMode(GlPolygonMode::kGlFill);
  }
}

static void RotateLevelLoading(size_t current_level_id, int step) {
  // all levels except [0] and [last] are in rotation
  auto new_id = (current_level_id + step) %
                (VisualScenes::Logic::visual_scenes.size() - 1);
  auto target = (new_id > 0 & new_id < 3) ? new_id : 1;
  pep::LoadLevelById(target);
}

void VisualScenes::Logic::Input::GotoNextLevel() {
#ifdef PEP_VERBOSE_GAME_LOGIC
  Terminal::ReportMsg("GotoNextLevel is called...");
#endif
  RotateLevelLoading(pep::GetCurrentLevelId(), +1);
}

void VisualScenes::Logic::Input::GotoPrevLevel() {
#ifdef PEP_VERBOSE_GAME_LOGIC
  Terminal::ReportMsg("GotoPrevLevel is called...");
#endif
  RotateLevelLoading(pep::GetCurrentLevelId(), -1);
}

static ColorMap::Color ShiftColor(ColorMap::Color name, int step) {
  auto code = (int)name + step;

  if (code <= ColorMap::gFirst) {
    return (ColorMap::Color)((int)ColorMap::Color::k_FIRST_ + 1);
  } else if (code < ColorMap::gLast) {
    return (ColorMap::Color)code;
  } else {
    return (ColorMap::Color)((int)ColorMap::Color::k_FIRST_ + 1);
  }
}

void VisualScenes::Logic::Input::DecreaseColor() {
#ifdef PEP_VERBOSE_GAME_LOGIC
  Terminal::ReportMsg("DecreaseColor is called...");
#endif
  auto current = pep::render::GetClearColor();
  auto col = ShiftColor(pep::render::FindClosestColor(current), -1);
  pep::render::SetClearColorName(col);
}

void VisualScenes::Logic::Input::IncreaseColor() {
#ifdef PEP_VERBOSE_GAME_LOGIC
  Terminal::ReportMsg("IncreaseColor is called...");
#endif
  auto current = pep::render::GetClearColor();
  auto col = ShiftColor(pep::render::FindClosestColor(current), +1);
  pep::render::SetClearColorName(col);
}

void VisualScenes::Logic::Input::Quit() { pep::LoadExitLevel(); }

void VisualScenes::Logic::bye_level::Transition() { pep::DoNothing(); }

void VisualScenes::Logic::bye_level::ExecuteTextWorldLogic() {
  pep::DoNothing();
}

void VisualScenes::Logic::bye_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}
