#ifndef INC_05_GUESS_NUMBER_GAME_OBJECTS_H
#define INC_05_GUESS_NUMBER_GAME_OBJECTS_H

#include <memory>
#include <variant>
#include <vector>

#include "engine/service/glrenderer/mesh.h"
#include "engine/service/game_update/sprite_image.h"

namespace visual_world_objects {

struct ViewableTriangle {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::VertexDescribed,
            {nullptr, nullptr}};
};

struct ViewableQuad {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::IndexDescribed,
            {nullptr, nullptr}};
};

struct TexturedQuad {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::IndexDescribed,
            {nullptr, nullptr}};
};

struct SpriteQuad {
  size_t game_sprite_multi_image_index;
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::IndexDescribed,
            {nullptr, nullptr}};
  SpriteImage sprite_image;
};

using Type = std::variant<ViewableTriangle, ViewableQuad, TexturedQuad,
                          SpriteQuad, std::monostate>;

// NOTE: +1 to NVI refactoring option
Mesh GetMesh(const Type& vwo);

}  // namespace visual_world_objects

#endif  // INC_05_GUESS_NUMBER_GAME_OBJECTS_H
