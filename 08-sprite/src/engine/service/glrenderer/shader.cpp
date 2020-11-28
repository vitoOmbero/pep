#include "engine/service/glrenderer/shader.h"

#include "utils/file_to_string.h"
#include "utils/terminal.h"

namespace gl_rendering_target {

Shader::Shader(ShaderType type,
               gl_rendering_target::RenderingTargetPackPointer rtpp,
               const char *source_full_path) {
#ifdef PEP_DEBUG
  if (source_full_path == nullptr || rtpp.n_vdp == 0)
    Terminal::ReportErr("Can't create a valid Shader, bad arguments!");
#endif
  type_ = type;

  sources_ = FileToString(source_full_path);

  for (int i = 0; i < rtpp.n_aps; ++i) {
    auto scheme = rtpp.aps[i].scheme;
    attribute_locations_[scheme] = i;
  }
}

void Shader::AddUniform(std::string name, GLint location) {
  uniform_locations_[name] = location;
}

GLint Shader::getUniformLocation(std::string name) const {
  if (uniform_locations_.count(name))
    return uniform_locations_.at(name);
  else
    return -1;
}

ShaderType Shader::getType() const { return type_; }

const std::string &Shader::getSources() const { return sources_; }

}  // namespace gl_rendering_target