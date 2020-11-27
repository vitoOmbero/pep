#ifndef LOOP_H
#define LOOP_H

#include <glad/glad.h>

#include <map>

#include "attribute.h"
#include "game_objects.h"
#include "gl_color.h"
#include "gl_rendering_target.h"
#include "mesh.h"
#include "shader_pack.h"
#include "vector"

class GlRenderer {
 public:
  GlRenderer();

  // TODO:  iterators are needed only
  void Init(const std::vector<visual_world_objects::Type>& vwo);

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

  std::vector<GLuint> v_target_shaders_;
  std::vector<GLsizei> v_target_sizes;

  std::vector<GLuint> ebo_;

  std::vector<GLuint> i_target_shaders_;
  std::vector<GLsizei> i_target_sizes_;
  std::vector<GLvoid*> i_target_offsets_;

  std::multimap<GLuint, GLuint> i_target_textures_;
  std::multimap<GLuint, std::string> i_target_uniforms_;

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
      const visual_world_objects::Type& vwo);

  void CreateIndexedTarget(const visual_world_objects::Type& vwo,
                           unsigned char target_index);
  void CreateUnIndexedTarget(const visual_world_objects::Type& vwo,
                             unsigned char target_index);

  void CreateVbo();

  void LoadTexture(const visual_world_objects::Type& vwo);

  void CookShaderProgram(const visual_world_objects::Type& vwo,
                         std::vector<GLuint>& shaders_container);

  void ProcessRenderingTargetK11(const visual_world_objects::Type& vwo,
                                 unsigned char target_index);
  void ProcessRenderingTargetK1N(const visual_world_objects::Type& vwo);
};

#endif  // LOOP_H
