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

using Type =
    std::variant<ViewableTriangle, ViewableQuad, TexturedQuad, std::monostate>;

// NOTE: +1 to NVI refactoring option
Mesh GetMesh(const Type& vwo);


}  // namespace visual_world_objects

#endif  // INC_05_GUESS_NUMBER_GAME_OBJECTS_H
