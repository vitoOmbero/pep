#ifndef INC_05_GUESS_NUMBER_GAME_OBJECTS_H
#define INC_05_GUESS_NUMBER_GAME_OBJECTS_H

#include <memory>
#include <variant>
#include <vector>

#include "engine/service/glrenderer/mesh.h"

namespace visual_world_objects {

struct Viewable {
  Mesh mesh{{nullptr, nullptr, 0, 0},
            RenderingTargetType::VertexDescribed,
            {"", "", 0, nullptr}};
};

using Type = std::variant<Viewable, std::monostate>;
}  // namespace visual_world_objects

#endif  // INC_05_GUESS_NUMBER_GAME_OBJECTS_H
