#include "service/game_update/sprite_image.h"

unsigned char *&SpriteImage::operator[](size_t n) { return images_[n]; }

const unsigned char *&SpriteImage::at(size_t n) const {
  return (const_reference)images_.at(n);
}

int SpriteImage::getWidth() const {
  return width_;
}

void SpriteImage::setWidth(int width) {
  width_ = width;
}

int SpriteImage::getHeight() const {
  return height_;
}

void SpriteImage::setHeight(int height) {
  height_ = height;
}
