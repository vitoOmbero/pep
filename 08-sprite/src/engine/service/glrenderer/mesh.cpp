#include "service/glrenderer/mesh.h"

#include <algorithm>
#include <utility>

#include "service/glrenderer/attribute.h"

Mesh::Mesh(gl_rendering_target::RenderingTargetPackPointer rtpp,
           RenderingTargetType rendering_target_type,
           gl_rendering_target::ShaderPack shader_pack,
           DrawingSpec drawing_spec, std::string texture_src)
    : rtpp_{rtpp},
      shader_pack_{shader_pack},
      drawing_spec_{drawing_spec},
      rendering_target_type_{rendering_target_type},
      texture_{std::move(texture_src)} {}

Mesh::Mesh(const Mesh& another)
    : rtpp_{another.rtpp_},
      drawing_spec_{another.drawing_spec_},
      shader_pack_{another.shader_pack_},
      rendering_target_type_{another.rendering_target_type_},
      texture_{another.texture_} {}

Mesh& Mesh::operator=(const Mesh& another) {
  // TODO: where is the resourse magament?
  // NOTE: why not default? is it final version?

  this->rtpp_ = another.rtpp_;
  this->drawing_spec_ = another.drawing_spec_;
  this->shader_pack_ = another.shader_pack_;
  this->rendering_target_type_ = another.rendering_target_type_;
  this->texture_ = another.texture_;
  return *this;
}

// NOTE:     how about to really free resourses?
Mesh::Mesh(Mesh&& another) noexcept
    : rtpp_{another.rtpp_},
      drawing_spec_{another.drawing_spec_},
      shader_pack_{another.shader_pack_},
      rendering_target_type_{another.rendering_target_type_},
      texture_{std::move(another.texture_)} {}

Mesh& Mesh::operator=(Mesh&& another) noexcept {
  if (this != &another) {
    this->rtpp_ = another.rtpp_;
    this->drawing_spec_ = std::move(another.drawing_spec_);
    this->shader_pack_ = std::move(another.shader_pack_);
    this->rendering_target_type_ = std::move(another.rendering_target_type_);
    this->texture_ = std::move(another.texture_);
  }
  return *this;
}

DrawingSpec Mesh::getDrawingSpec() const { return drawing_spec_; }

void Mesh::setDescriptor(const DrawingSpec& descriptor) {
  drawing_spec_ = descriptor;
}

gl_rendering_target::RenderingTargetPackPointer Mesh::getRtpp() const {
  return rtpp_;
}

void Mesh::setRtpp(
    const gl_rendering_target::RenderingTargetPackPointer& value) {
  rtpp_ = value;
}

gl_rendering_target::ShaderPack Mesh::getShaderPack() const {
  return shader_pack_;
}

void Mesh::setShaderPack(const gl_rendering_target::ShaderPack& shader_pack) {
  shader_pack_ = shader_pack;
}

RenderingTargetType Mesh::getRenderingTargetType() const {
  return rendering_target_type_;
}

void Mesh::setRenderingTargetType(RenderingTargetType rendering_target_type) {
  rendering_target_type_ = rendering_target_type;
}

const Texture& Mesh::getTexture() const { return texture_; }

void Mesh::setTexture(const Texture& texture) { texture_ = texture; }
