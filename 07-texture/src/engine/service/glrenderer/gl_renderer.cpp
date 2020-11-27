#include "service/glrenderer/gl_renderer.h"

#include <algorithm>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "utils/gl_enum.h"
#include "utils/terminal.h"

#define TAG "GlRenderer >>"

#define GL_CHECK()                                                 \
  {                                                                \
    const unsigned int err = glGetError();                         \
    if (err != GL_NO_ERROR) {                                      \
      switch (err) {                                               \
        case GL_INVALID_ENUM:                                      \
          Terminal::ReportErr("GL_INVALID_ENUM");                  \
          break;                                                   \
        case GL_INVALID_VALUE:                                     \
          Terminal::ReportErr("GL_INVALID_VALUE");                 \
          break;                                                   \
        case GL_INVALID_OPERATION:                                 \
          Terminal::ReportErr("GL_INVALID_OPERATION");             \
          break;                                                   \
        case GL_INVALID_FRAMEBUFFER_OPERATION:                     \
          Terminal::ReportErr("GL_INVALID_FRAMEBUFFER_OPERATION"); \
          break;                                                   \
        case GL_OUT_OF_MEMORY:                                     \
          Terminal::ReportErr("GL_OUT_OF_MEMORY");                 \
          break;                                                   \
        default:                                                   \
          Terminal::ReportErr("Unknown GL error");                 \
      }                                                            \
      assert(false);                                               \
    }                                                              \
  }

GlRenderer::GlRenderer() {
  // glViewport(0, 0, 640, 480);

  glGenVertexArrays(1, &vao_);
  GL_CHECK()
}

void GlRenderer::Init(const std::vector<visual_world_objects::Type> &v) {
  if (v.empty()) {
#ifdef PEP_DEBUG
    Terminal::ReportErr("Wrong mesh list for current game level!");
#endif
    return;
  }

#ifdef RENDERER_VERBOSE
  {
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    GL_CHECK()
    Terminal::ReportMsg(TAG "maxVertexAttribs: ");
    Terminal::ReportMsg(std::to_string(maxVertexAttribs));
  }
#endif

  std::for_each(v.begin(), v.end(), [&](const visual_world_objects::Type &vwo) {
    // TODO: refactor and add checks for explicit rendering target type
    // NOTE: std::variant of visual world objects ->> NVI for v.w.o.
    // mesh.getRenderingTargetType()

    ProcessMeshBoundedRenderingTargets(vwo);
  });
}

// current algorithm ignores rendering target processing in case of shared ADP
// for VertexAttributeData::Composition::kNM
void GlRenderer::ProcessMeshBoundedRenderingTargets(
    const visual_world_objects::Type &vwo) {
  using gl_rendering_target::AttributePackSpecification;
  using gl_rendering_target::RenderingTargetPackPointer;
  using gl_rendering_target::VertexDataPointer;

  const auto &mesh = visual_world_objects::GetMesh(vwo);

  const auto rtpp = mesh.getRtpp();
  DrawingSpec ds = mesh.getDrawingSpec();
  const gl_rendering_target::ShaderPack &sp = mesh.getShaderPack();

#ifdef RENDERER_VERBOSE
  if (rtpp.n_aps == 0 && rtpp.n_vdp == 0) {
    Terminal::ReportErr(TAG "Warning: RenderingTargetPackPointer at address");
    Terminal::ReportErr(
        static_cast<void *>(const_cast<RenderingTargetPackPointer *>(&rtpp)));
    Terminal::ReportErr("may be ill-formed. ");

    Terminal::ReportErr("RenderingTargetPack size is zero.");
  }
#endif

  size_t aps_last = rtpp.n_aps - 1;
  size_t vdp_last = rtpp.n_vdp - 1;

#ifdef PEP_DEBUG
  if (aps_last != vdp_last && vdp_last != 0) {
    Terminal::ReportErr(TAG "Warning: RenderingTargetPackPointer at address");
    Terminal::ReportErr(
        static_cast<void *>(const_cast<RenderingTargetPackPointer *>(&rtpp)));
    Terminal::ReportErr("may be ill-formed. ");

    Terminal::ReportErr("RenderingTargetPack data is not correctly composed.");
    Terminal::ReportErr("CompositionCase::k1N needs 1 vdp only.");
  }
#endif

  // TODO: refactor this
  // NOTE: with new approach, it is possible to reduce even more code
  if (vdp_last == 1 && aps_last == vdp_last) {
    ProcessRenderingTargetK11(vwo, 0);
  } else if (aps_last == vdp_last)
    for (unsigned char i = 0; i < rtpp.n_aps; ++i)
      ProcessRenderingTargetK11(vwo, i);
  else
    ProcessRenderingTargetK1N(vwo);
}

void GlRenderer::LoadTexture(const visual_world_objects::Type &vwo) {
  const auto &mesh = visual_world_objects::GetMesh(vwo);
  auto tex = mesh.getTexture();

  if (tex.texture_asset_path.empty()) return;

  int width, height, components;

  unsigned char *imageData = stbi_load(tex.texture_asset_path.data(), &width,
                                       &height, &components, STBI_rgb_alpha);

  if (imageData == nullptr) {
    Terminal::ReportMsg(TAG "Error loading texture :");
    Terminal::ReportMsg(tex.texture_asset_path);
  }

  // invert
  int widthInBytes = width * 4;
  unsigned char *top = nullptr;
  unsigned char *bottom = nullptr;
  unsigned char temp = 0;
  int halfHeight = height / 2;
  for (int row = 0; row < halfHeight; row++) {
    top = imageData + row * widthInBytes;
    bottom = imageData + (height - row - 1) * widthInBytes;
    for (int col = 0; col < widthInBytes; col++) {
      temp = *top;
      *top = *bottom;
      *bottom = temp;
      top++;
      bottom++;
    }
  }

  GLuint texture;
  glGenTextures(1, &texture);
  i_target_textures_.insert({ebo_[ebo_.size() - 1], texture});
  glBindTexture(GL_TEXTURE_2D, texture);

  // NOTE:
  // GL_CLAMP_TO_EDGE
  // GL_REPEAT
  // GL_MIRRORED_REPEAT
  // GL_CLAMP_TO_BORDER
  // GL_LINEAR
  // GL_NEAREST

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, imageData);

  if (tex.should_mipmaps_be_generated) glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(imageData);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void GlRenderer::CreateIndexedTarget(const visual_world_objects::Type &vwo,
                                     unsigned char target_index) {
  const auto &mesh = visual_world_objects::GetMesh(vwo);
  const auto *vdp = &mesh.getRtpp().vdp[target_index];
  DrawingSpec ds = mesh.getDrawingSpec();
  const auto &sp = mesh.getShaderPack();

  GLuint ibo;
  glGenBuffers(1, &ibo);
  GL_CHECK()
  ebo_.push_back(ibo);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  GL_CHECK()

  auto *offset = reinterpret_cast<GLvoid *>(accumulative_ebo_offset_);
  i_target_offsets_.push_back(offset);
  i_target_sizes_.push_back(vdp->n_indices);

  accumulative_ebo_offset_ += SizeOfIndexData(vdp);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOfIndexData(vdp), vdp->i_data,
               DrawingSpecToGlEnum(ds));
  GL_CHECK()

  CookShaderProgram(vwo, i_target_shaders_);
  LoadTexture(vwo);
}

void GlRenderer::CreateUnIndexedTarget(const visual_world_objects::Type &vwo,
                                       unsigned char target_index) {
  const auto &mesh = visual_world_objects::GetMesh(vwo);
  const auto *vdp = &mesh.getRtpp().vdp[target_index];
  const auto &sp = mesh.getShaderPack();

  v_target_sizes.push_back(vdp->n_vertices);

  //  TODO: textures for unindexed targets?

  CookShaderProgram(vwo, v_target_shaders_);
}

void GlRenderer::CreateVbo() {
  glBindVertexArray(vao_);
  GL_CHECK()

  GLuint vbo;
  glGenBuffers(1, &vbo);
  GL_CHECK()
  vbo_.push_back(vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GL_CHECK()
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

void GlRenderer::CookShaderProgram(const visual_world_objects::Type &vwo,
                                   std::vector<GLuint> &shaders_container) {
  const gl_rendering_target::ShaderPack &sp =
      visual_world_objects::GetMesh(vwo).getShaderPack();

  // create vertex shader
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  GL_CHECK()

  std::string v = sp.vertex_shader->getSources();

  const GLchar *vsrc = v.data();

#ifdef RENDERER_VERBOSE
  {
    Terminal::ReportMsg(TAG "Loaded vertex shader:");
    Terminal::ReportMsg(v);
    Terminal::ReportMsg(TAG "EOF");
  }
#endif

  glShaderSource(vs, 1, &vsrc, nullptr);
  GL_CHECK()
  glCompileShader(vs);
  GL_CHECK()

  // check for compile errors
  GLint result;
  GLchar infoLog[1024];
  glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
  GL_CHECK()
  if (!result) {
    glGetShaderInfoLog(vs, sizeof(infoLog), nullptr, infoLog);
    GL_CHECK()
    Terminal::ReportErr("Error! Vertex shader failed to compile. ");
    Terminal::ReportErr(infoLog);

    return;
  }

  // create fragment shader
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  GL_CHECK()

  v = sp.fragment_shader->getSources();
  const GLchar *fsrc = v.data();

#ifdef RENDERER_VERBOSE
  {
    Terminal::ReportMsg(TAG "Loaded fragment shader:");
    Terminal::ReportMsg(v);
    Terminal::ReportMsg(TAG "EOF");
  }
#endif

  glShaderSource(fs, 1, &fsrc, nullptr);
  GL_CHECK()
  glCompileShader(fs);
  GL_CHECK()

  // check
  glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(fs, sizeof(infoLog), nullptr, infoLog);
    Terminal::ReportErr("Error! Fragment shader failed to compile. ");
    Terminal::ReportErr(infoLog);

    return;
  }

  // create shader program and link shaders to program
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  GL_CHECK()
  glAttachShader(shader_program, fs);
  GL_CHECK()
  glLinkProgram(shader_program);
  GL_CHECK()

  // check
  glGetProgramiv(shader_program, GL_LINK_STATUS, &result);
  GL_CHECK()
  if (!result) {
    glGetProgramInfoLog(shader_program, sizeof(infoLog), nullptr, infoLog);
    Terminal::ReportErr("Error! Shader program linker failure ");
    Terminal::ReportErr(infoLog);

    return;
  }

  // clean up shaders, they are linked already
  glDeleteShader(vs);
  GL_CHECK()
  glDeleteShader(fs);
  GL_CHECK()

  // save program
  shaders_container.emplace_back(shader_program);
}

#pragma clang diagnostic pop

void GlRenderer::ProcessRenderingTargetK11(
    const visual_world_objects::Type &vwo, unsigned char target_index) {
  using namespace gl_rendering_target;

  const auto &mesh = visual_world_objects::GetMesh(vwo);
  const auto &rtpp = mesh.getRtpp();
  auto ds = mesh.getDrawingSpec();
  const auto &sp = mesh.getShaderPack();

#ifdef RENDERER_VERBOSE
  Terminal::ReportMsg(TAG "Processing case k11");
#endif
  CreateVbo();
  glBufferData(GL_ARRAY_BUFFER,
               gl_rendering_target::SizeOfVertexData(rtpp, target_index),
               rtpp.vdp[target_index].v_data, DrawingSpecToGlEnum(ds));
  GL_CHECK()
#ifdef RENDERER_VERBOSE
  if (rtpp.aps[target_index].layout != AttributeDataLayout::kContiguous) {
    Terminal::ReportErr(TAG "Warning: VertexAttributeData at address");
    Terminal::ReportErr(
        static_cast<void *>(const_cast<RenderingTargetPackPointer *>(&rtpp)));
    Terminal::ReportErr("may be ill-formed. ");

    Terminal::ReportErr(TAG "AttributeDataLayout should be: ");
    Terminal::ReportErr(std::to_string((int)AttributeDataLayout::kContiguous));
    Terminal::ReportErr("is: ");
    Terminal::ReportErr(std::to_string((int)rtpp.aps[target_index].layout));
  }
#endif

  GLuint location_counter_{0};

  glVertexAttribPointer(
      location_counter_,
      attribute::RuntimeMap::Get(rtpp.aps[target_index].scheme)->attributes_n,
      rtpp.aps[target_index].type_code,
      BooleanToGlBoolConstant(rtpp.aps[target_index].is_data_NOT_normalized),
      rtpp.aps[target_index].stride, rtpp.aps[target_index].offset);
  GL_CHECK()

  glEnableVertexAttribArray(location_counter_);
  GL_CHECK()

  if (rtpp.vdp[target_index].i_data != nullptr) {
    CreateIndexedTarget(vwo, target_index);
  } else {
    CreateUnIndexedTarget(vwo, target_index);
  }
}

void GlRenderer::ProcessRenderingTargetK1N(
    const visual_world_objects::Type &vwo) {
#ifdef RENDERER_VERBOSE
  Terminal::ReportMsg(TAG "Processing case k1N");
#endif

  const auto &mesh = visual_world_objects::GetMesh(vwo);
  const auto &rtpp = mesh.getRtpp();
  auto ds = mesh.getDrawingSpec();
  const auto &sp = mesh.getShaderPack();

  CreateVbo();

  auto s = gl_rendering_target::SizeOfVertexData(rtpp, 0);
  auto d = rtpp.vdp[0].v_data;
  auto ddss = DrawingSpecToGlEnum(ds);

  glBufferData(GL_ARRAY_BUFFER, s, d, ddss);
  GL_CHECK()

#ifdef RENDERER_VERBOSE
  if (rtpp.aps[0].layout !=
      gl_rendering_target::AttributeDataLayout::kInterleaved) {
    Terminal::ReportErr(TAG "Warning: RenderingTargetPackPointer at adress");
    Terminal::ReportErr(static_cast<void *>(
        const_cast<gl_rendering_target::RenderingTargetPackPointer *>(&rtpp)));
    Terminal::ReportErr("may be ill-formed. ");

    Terminal::ReportErr(TAG "VertexAttributeData::CompositionCase should be: ");
    Terminal::ReportErr(std::to_string(
        (int)gl_rendering_target::AttributeDataLayout::kInterleaved));
    Terminal::ReportErr("is: ");
    Terminal::ReportErr(std::to_string((int)rtpp.aps[0].layout));
  }
#endif

  glBindVertexArray(vao_);
  GL_CHECK()

  GLuint location_counter_{0};

  for (unsigned char i = 0; i < rtpp.n_aps; ++i) {
    auto location = location_counter_ + i;
    auto number = attribute::RuntimeMap::Get(rtpp.aps[i].scheme)->attributes_n;
    auto gltype = rtpp.aps[i].type_code;
    auto glbool = BooleanToGlBoolConstant(rtpp.aps[i].is_data_NOT_normalized);
    auto stride = rtpp.aps[i].stride;
    auto offset = rtpp.aps[i].offset;

    glVertexAttribPointer(location, number, gltype, glbool, stride, offset);
    GL_CHECK()

    glEnableVertexAttribArray(location);
    GL_CHECK()
  }

  if (rtpp.vdp[0].i_data != nullptr) {
    CreateIndexedTarget(vwo, 0);
  } else {
    CreateUnIndexedTarget(vwo, 0);
  }
}

void GlRenderer::RenderFrame() {
#ifdef RENDERER_VERBOSE
  static bool already_reported = false;

  if (!already_reported)
    if (vbo_.empty() || v_target_shaders_.empty()) {
      if (already_reported) return;

      Terminal::ReportErr("GlRenderer is not initialized.");
      already_reported = true;
      return;
    }
#endif

  glClearColor(clear_color_.red, clear_color_.green, clear_color_.blue,
               clear_color_.alpha);
  GL_CHECK()
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  GL_CHECK()

  // Render targets is working only with one vao (currently)

  // vertex targets rendering
  glBindVertexArray(vao_);
  GL_CHECK()

  for (size_t i = 0; i < v_target_sizes.size(); ++i) {
    glUseProgram(v_target_shaders_[i]);
    GL_CHECK()
    glDrawArrays(GL_TRIANGLES, 0, v_target_sizes[i]);
    GL_CHECK()
  }


  if (!ebo_.empty()) {
    for (size_t i = 0; i < ebo_.size(); ++i) {

      glUseProgram(i_target_shaders_[i]);
      GL_CHECK()

      // bind textures
      if (i_target_textures_.count(ebo_[i])) {
        auto range = i_target_textures_.equal_range(ebo_[i]);
        int counter = 0;
        for (auto j = range.first; j != range.second; ++j) {
          assert(counter >= 0 && counter < 80);  // see khronos docs
          glActiveTexture(GL_TEXTURE0 + counter);
          glBindTexture(GL_TEXTURE_2D, j->second);
/*        using by defult
          glUniform1i(glGetUniformLocation(i_target_shaders_[i], "texture_s1"),
                      0);
*/
          ++counter;
        }
        //
      }

      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_[i]);
      glBindVertexArray(vao_);
      GL_CHECK()
      glDrawElements(GL_TRIANGLES, i_target_sizes_[i], GL_UNSIGNED_INT,
                     i_target_offsets_[i]);
      GL_CHECK()
    }
  }

  glBindVertexArray(0);
  GL_CHECK()
}

GlRenderer::~GlRenderer() {
  glDeleteVertexArrays(1, &vao_);
  for (auto i : v_target_shaders_) glDeleteProgram(i);
  for (auto i : i_target_shaders_) glDeleteProgram(i);
  for (auto i : vbo_) glDeleteBuffers(1, &i);
  for (auto i : ebo_) glDeleteBuffers(1, &i);
  for (auto i : i_target_textures_) glDeleteTextures(1, &i.second);

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

void GlRenderer::SwitchGlPolygonMode(GlPolygonMode mode) {
  glPolygonMode(GL_FRONT_AND_BACK, GlPolygonModeToGlEnum(mode));
}

const gl_color &GlRenderer::getClearColor() const { return clear_color_; }

void GlRenderer::setClearColor(const gl_color &clear_color) {
  clear_color_ = clear_color;
}

#pragma clang diagnostic pop
