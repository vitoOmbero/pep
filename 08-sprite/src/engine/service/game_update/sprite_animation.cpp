#include "service/game_update/sprite_animation.h"

const std::string SpriteAnimation::default_loop = "default";

SpriteAnimation::SpriteAnimation(SpriteImage& sprite_image)
    : sprite_image_(std::move(sprite_image)) {
  for (size_t i = 0; i < sprite_image.size(); ++i)
    loops_.insert({default_loop, i});

}

size_t SpriteAnimation::getFps() const {
  return fps_;
}

const std::string &SpriteAnimation::getActiveLoop() const {
  return active_loop_;
}

bool SpriteAnimation::setActiveLoop(std::string name_id) {
  bool result = loops_.count(name_id);

  if(result){
    active_loop_ = name_id;
  }

  return result;
}

bool SpriteAnimation::AddLoop(std::string name_id, std::vector<size_t> indices) {
  bool result = !loops_.count(name_id);

  if (result){
    for (size_t i = 0; i < indices.size(); ++i)
      loops_.insert({default_loop, indices[i]});
  }

  return result;
}

void SpriteAnimation::setFps(size_t fps) {
  fps_ = fps;
}
