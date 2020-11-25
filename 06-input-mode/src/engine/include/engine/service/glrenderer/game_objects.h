#ifndef INC_05_GUESS_NUMBER_GAME_OBJECTS_H
#define INC_05_GUESS_NUMBER_GAME_OBJECTS_H

#include <memory>
#include <variant>
#include <vector>

#include "engine/service/glrenderer/mesh.h"

namespace visual_world_objects {

struct ViewableTriangle {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::VertexDescribed,
            {"", "", 0, nullptr}};
};

struct ViewableQuad {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::IndexDescribed,
            {"", "", 0, nullptr}};
};

using Type = std::variant<ViewableTriangle, ViewableQuad, std::monostate>;
}  // namespace visual_world_objects

#endif  // INC_05_GUESS_NUMBER_GAME_OBJECTS_H
