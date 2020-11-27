#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <glad/glad.h>

namespace attribute {

enum Type : unsigned char {
  kPosition,
  kColor,
  kUvCoords,
};

enum Value : unsigned char {
  kPosNormalizedXCoord,
  kPosNormalizedYCoord,
  kPosNormalizedZCoord,

  kColRedChannel,
  kColGreenChannel,
  kColBlueChannel,
  kColAlphaChannel,

  kUvNormalizedUCoord,
  kUvNormalizedVCoord,
};

enum Scheme : unsigned char {
  kPosition2d = 0,
  kPosition3d = 1,
  kColorRgb = 2,
  kColorRgba = 3,
  kUvCoords2d = 4
};

namespace scheme {

static inline const Value position_2d[]{kPosNormalizedXCoord,
                                        kPosNormalizedYCoord};
static inline const GLint position_2d_attr_n = 2;
static inline const Value position_3d[]{
    kPosNormalizedXCoord, kPosNormalizedYCoord, kPosNormalizedZCoord};
static inline const GLint position_3d_attr_n = 3;
static inline const Value color_rgb[]{kColRedChannel, kColGreenChannel,
                                      kColBlueChannel};
static inline const GLint color_rgb_attr_n = 3;
static inline const Value color_rgba[]{kColRedChannel, kColGreenChannel,
                                       kColBlueChannel, kColAlphaChannel};
static inline const GLint color_rgba_attr_n = 4;
static inline const Value uv_2d[]{kUvNormalizedUCoord, kUvNormalizedVCoord};
static inline const GLint uv_2d_n = 2;
}  // namespace scheme

#pragma pack(push, 1)
struct PackDescriptionValue {
  ///> value of attribute (e.g. x_coord, red_channel ...)
  const Value* values;
  ///> number of attribute values in scheme
  const GLint attributes_n;
  ///> type of attribute (e.g. position, color ...)
  const Type type;
};
#pragma pack(pop)

// clang-format off
template <Scheme key> struct PackDescription {   static PackDescriptionValue values;    };

template <> struct PackDescription<Scheme::kPosition2d> { static PackDescriptionValue values; };

template <> struct PackDescription<Scheme::kPosition3d> { static PackDescriptionValue values; };

template <> struct PackDescription<Scheme::kColorRgb> { static PackDescriptionValue values; };

template <> struct PackDescription<Scheme::kColorRgba> { static PackDescriptionValue values; };

template <> struct PackDescription<Scheme::kUvCoords2d> { static PackDescriptionValue values; };

// clang-format on

namespace RuntimeMap {

const PackDescriptionValue* Get(Scheme scheme);

}  // namespace RuntimeMap
}  // namespace attribute

#endif  // ATTRIBUTE_H
