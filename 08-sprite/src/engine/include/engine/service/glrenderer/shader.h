#ifndef INC_07_TEXTURED_OBJECTS_SHADER_H
#define INC_07_TEXTURED_OBJECTS_SHADER_H

#include <glad/glad.h>

#include <unordered_map>

#include "attribute.h"
#include "gl_rendering_target.h"

namespace gl_rendering_target {

enum class ShaderType {
  kVertex,
  kFragment,
};

class Shader final {
 public:
  Shader(ShaderType type, gl_rendering_target::RenderingTargetPackPointer rtpp,
         const char *source_full_path);

  ~Shader() = default;

  void AddUniform(std::string name, GLint location);

  GLint getUniformLocation(std::string name) const;

  ShaderType getType() const;

  const std::string &getSources() const;

 private:
  ShaderType type_;
  std::string sources_;
  std::unordered_map<attribute::Scheme, GLint> attribute_locations_{};
  std::unordered_map<std::string, GLint> uniform_locations_{};
};

}  // namespace gl_rendering_target
#endif  // INC_07_TEXTURED_OBJECTS_SHADER_H
