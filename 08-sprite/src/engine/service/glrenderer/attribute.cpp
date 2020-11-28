#include "engine/service/glrenderer/attribute.h"

namespace attribute {

// clang-format off


PackDescriptionValue PackDescription<Scheme::kPosition2d>::values = PackDescriptionValue{
    scheme::position_2d, scheme::position_2d_attr_n, Type::kPosition };

PackDescriptionValue PackDescription<Scheme::kPosition3d>::values = PackDescriptionValue{
    scheme::position_3d, scheme::position_3d_attr_n, Type::kPosition };

PackDescriptionValue PackDescription<Scheme::kColorRgb>::values = PackDescriptionValue{
    scheme::color_rgb, scheme::color_rgb_attr_n, Type::kColor };

PackDescriptionValue PackDescription<Scheme::kColorRgba>::values = PackDescriptionValue{
    scheme::color_rgba, scheme::color_rgba_attr_n, Type::kColor };

PackDescriptionValue PackDescription<Scheme::kUvCoords2d>::values = PackDescriptionValue{
    scheme::uv_2d, scheme::uv_2d_n, Type::kUvCoords };

// clang-format on

static PackDescriptionValue static_map[]{
    // NOTE: order must be the same as attribute::Scheme code
    PackDescription<Scheme::kPosition2d>::values,
    PackDescription<Scheme::kPosition3d>::values,
    PackDescription<Scheme::kColorRgb>::values,
    PackDescription<Scheme::kColorRgba>::values,
    PackDescription<Scheme::kUvCoords2d>::values,
};

const attribute::PackDescriptionValue* attribute::RuntimeMap::Get(
    attribute::Scheme scheme) {
  unsigned char index = static_cast<unsigned char>(scheme);
  return &static_map[index];
};

}  // namespace attribute
