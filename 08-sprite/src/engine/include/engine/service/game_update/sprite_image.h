#ifndef INC_07_TEXTURED_OBJECTS_SPRITE_IMAGE_H
#define INC_07_TEXTURED_OBJECTS_SPRITE_IMAGE_H

#include <vector>

class SpriteImage {
 public:
  using reference = unsigned char *&;
  using const_reference = const unsigned char *&;

  reference operator[](size_t n);
  [[nodiscard]] const_reference at(size_t n) const;

  inline void Add(unsigned char *image) { images_.push_back(image); };

  inline bool IsMultiImage() const { return images_.size() > 1; };

  inline size_t size() const { return images_.size(); };

  inline bool empty() const { return images_.empty(); };

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

private:
  std::vector<unsigned char *> images_{};
  int width_;
  int height_;
};

#endif  // INC_07_TEXTURED_OBJECTS_SPRITE_IMAGE_H
