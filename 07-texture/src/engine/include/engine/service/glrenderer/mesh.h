#ifndef MESH_H
#define MESH_H

#include <string>

#include "engine/utils/gl_enum.h"
#include "gl_rendering_target.h"
#include "shader.h"
#include "shader_pack.h"
#include "texture.h"

// NOTE: meshes do not support shared shaders yet

enum class RenderingTargetType {
  VertexDescribed,
  IndexDescribed,
};

class Mesh {
 public:
  Mesh(gl_rendering_target::RenderingTargetPackPointer rtpp_,
       RenderingTargetType rendering_target_type,
       gl_rendering_target::ShaderPack shader_pack,
       DrawingSpec drawing_spec = DrawingSpec::kStatic,
       std::string texture_src = "");

  // NOTE: no, they won't be default all the time
  Mesh(const Mesh& another);
  Mesh& operator=(const Mesh& another);
  Mesh(Mesh&& another) noexcept;
  Mesh& operator=(Mesh&& another) noexcept;

  [[nodiscard]] DrawingSpec getDrawingSpec() const;
  void setDescriptor(const DrawingSpec& descriptor);

  [[nodiscard]] gl_rendering_target::RenderingTargetPackPointer getRtpp() const;
  void setRtpp(const gl_rendering_target::RenderingTargetPackPointer& value);

  [[nodiscard]] gl_rendering_target::ShaderPack getShaderPack() const;
  void setShaderPack(const gl_rendering_target::ShaderPack& shader_pack);

  [[nodiscard]] RenderingTargetType getRenderingTargetType() const;

  void setRenderingTargetType(RenderingTargetType rendering_target_type);

  [[nodiscard]] const Texture& getTexture() const;

  void setTexture(const Texture& texture);

 private:
  gl_rendering_target::RenderingTargetPackPointer rtpp_;
  DrawingSpec drawing_spec_;
  gl_rendering_target::ShaderPack shader_pack_;
  RenderingTargetType rendering_target_type_;
  Texture texture_;
};

template <class T>
struct is_mesh {
  static const bool value = false;
};

template <>
struct is_mesh<Mesh> {
  static const bool value = true;
};
#endif  // MESH_H
