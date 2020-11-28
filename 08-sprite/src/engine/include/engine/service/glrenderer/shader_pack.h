#ifndef INC_07_TEXTURED_OBJECTS_SHADER_PACK_H
#define INC_07_TEXTURED_OBJECTS_SHADER_PACK_H

#include "shader.h"
namespace gl_rendering_target {
struct ShaderPack {
  Shader *vertex_shader;
  Shader *fragment_shader;
};
}  // namespace gl_rendering_target
#endif  // INC_07_TEXTURED_OBJECTS_SHADER_PACK_H
