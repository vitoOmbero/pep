#include "visual_scenes/logic.h"

#include "engine/pep.h"

void VisualScenes::Logic::intro_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void VisualScenes::Logic::intro_level::ExecuteTextWorldLogic() { pep::DoNothing(); }

void VisualScenes::Logic::intro_level::Transition() { pep::LoadLevelById(1); }


void VisualScenes::Logic::triangle_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void VisualScenes::Logic::triangle_level::ExecuteTextWorldLogic() {

}

void VisualScenes::Logic::triangle_level::Transition() {

}

void VisualScenes::Logic::quad_level::OnLoad() {
  pep::LoadTextWorldObjectById(0);
}

void VisualScenes::Logic::quad_level::ExecuteTextWorldLogic() {

}

void VisualScenes::Logic::quad_level::Transition() {

}
