#ifndef INC_07_TEXTURED_OBJECTS_SPRITE_ANIMATION_H
#define INC_07_TEXTURED_OBJECTS_SPRITE_ANIMATION_H

#include "sprite_image.h"

#include <string>
#include <unordered_map>


class SpriteAnimation{
public:

    explicit SpriteAnimation(SpriteImage& sprite_image);

    size_t getFps() const;
    void setFps(size_t fps);

    static const std::string default_loop;
    bool AddLoop (std::string name_id, std::vector<size_t> indices);

    bool setActiveLoop(std::string name_id);
    const std::string &getActiveLoop() const;

    void Play();
    void Pause();
    void Stop();

private:
    SpriteImage sprite_image_;
    std::unordered_multimap<std::string, size_t> loops_{};
    std::string active_loop_;
    size_t fps_{24};
};

#endif //INC_07_TEXTURED_OBJECTS_SPRITE_ANIMATION_H
