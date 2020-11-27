#include "service/input_processing/input_processing_service.h"

#include <algorithm>

#include "service/input_processing/sdl_bindings.h"

static const InputModeVector *modes_{nullptr};
static const InputMode *active_mode_{nullptr};

void InputProcessingService::ProcessKeyboardEvent(
    const SDL_KeyboardEvent &sdl_keyboard_event) {
  // is needed?
  if (nullptr == active_mode_) return;

  // is produced?
  if (active_mode_->key_map.empty()) return;

  auto state = SDL_GetKeyboardState(nullptr);
  auto sdl_scan_code = SDL_GetScancodeFromKey(sdl_keyboard_event.keysym.sym);

  // is known?
  if (sdlk_bindings.count(sdl_scan_code) == 0) return;

  auto keycode = sdlk_bindings.at(sdl_scan_code);

  const auto it = std::find_if(
      begin(active_mode_->key_map), end(active_mode_->key_map),
      [&keycode](const std::pair<const KeyName, input_handler_t> &p) {
        return p.first == keycode;
      });

  // is found?
  if (it == end(active_mode_->key_map)) return;

  // is released?
  if (sdl_keyboard_event.state == SDL_RELEASED && sdl_keyboard_event.type == SDL_KEYUP)
    // run by raw function pointer
    active_mode_->key_map.at(keycode)();
}

void InputProcessingService::Init(const InputModeVector *modes) {
  modes_ = modes;
}

void InputProcessingService::Destroy() { modes_ = nullptr; }

void InputProcessingService::EnableMode(size_t id) {
  active_mode_ = &modes_->at(id);
}
