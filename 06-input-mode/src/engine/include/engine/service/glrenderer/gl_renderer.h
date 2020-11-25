#ifndef LOOP_H
#define LOOP_H

#include <glad/glad.h>

#include "attribute.h"
#include "gl_color.h"
#include "gl_rendering_target.h"
#include "mesh.h"
#include "vector"

class GlRenderer {
 public:
  GlRenderer();

  // TODO:  iterators are needed only
  void Init(const std::vector<Mesh>& meshes);

  /**
   * @brief Start Loop starts and checks the statement at each iteration
   */
  void RenderFrame();

  ~GlRenderer();

  void SwitchGlPolygonMode(GlPolygonMode mode);

  [[nodiscard]] const gl_color& getClearColor() const;

  void setClearColor(const gl_color& clear_color);

 private:
  std::vector<GLuint> vbo_;
  std::vector<GLuint> ebo_;

  std::vector<uint32_t> v_target_id_;
  std::vector<GLuint> v_target_shaders_;
  std::vector<GLsizei> v_target_sizes;

  std::vector<uint32_t> i_target_id_;
  std::vector<GLuint> i_target_shaders_;
  std::vector<GLsizei> i_target_sizes_;
  std::vector<GLvoid*> i_target_offsets_;
  size_t accumulative_ebo_offset_{0};

  gl_color clear_color_{.24, .12, .24, 1.};
  GLuint vao_{0};

  /**
   * @brief ProcessMeshBoundedRenderingTargets Create vbo, ebo and register
   * all required rendering targets (implicitly)
   * @param vao_name Vertex array object name for vertex buffer objects be
   * binded
   * @param vad pointer to Vertex Attribute Data object
   * @param ds Drawing specification for rendering targets
   * @param sp Shaders will be registered for indexed target only
   */
  void ProcessMeshBoundedRenderingTargets(
      gl_rendering_target::RenderingTargetPackPointer rtpp, DrawingSpec ds,
      const gl_rendering_target::ShaderPack& sp);

  void CreateIndexedTarget(const gl_rendering_target::VertexDataPointer* vdp,
                           DrawingSpec ds,
                           const gl_rendering_target::ShaderPack& sp);
  void CreateUnIndexedTarget(const gl_rendering_target::VertexDataPointer* vdp,
                             const gl_rendering_target::ShaderPack& sp);

  void CreateVbo();

  void CookShaderProgram(const gl_rendering_target::ShaderPack& sp,
                         std::vector<GLuint>& shaders_container);

  void ProcessRenderingTargetK11(
      gl_rendering_target::RenderingTargetPackPointer rtpp, DrawingSpec ds,
      unsigned char target_index, const gl_rendering_target::ShaderPack& sp);
  void ProcessRenderingTargetK1N(
      gl_rendering_target::RenderingTargetPackPointer rtpp, DrawingSpec ds,
      const gl_rendering_target::ShaderPack& sp);
};

#endif  // LOOP_H
