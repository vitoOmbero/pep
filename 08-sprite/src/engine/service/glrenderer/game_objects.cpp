#include "engine/service/glrenderer/game_objects.h"

Mesh visual_world_objects::GetMesh(
    const visual_world_objects::Type &vwo) {

  if (std::get_if<visual_world_objects::ViewableTriangle>(&vwo) != nullptr) {
    auto vrt = std::get<visual_world_objects::ViewableTriangle>(vwo);
    return vrt.mesh;
  }

  if (std::get_if<visual_world_objects::ViewableQuad>(&vwo) != nullptr) {
    auto vrt = std::get<visual_world_objects::ViewableQuad>(vwo);
    return vrt.mesh;
  }

  if (std::get_if<visual_world_objects::TexturedQuad>(&vwo) != nullptr) {
    auto vrt = std::get<visual_world_objects::TexturedQuad>(vwo);
    return vrt.mesh;
  }

  if (std::get_if<visual_world_objects::SpriteQuad>(&vwo) != nullptr) {
    auto vrt = std::get<visual_world_objects::SpriteQuad>(vwo);
    return vrt.mesh;
  }

}
