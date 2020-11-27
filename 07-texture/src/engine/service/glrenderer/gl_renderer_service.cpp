#include "service/glrenderer/gl_renderer_service.h"

#include <memory>

#include "engine/configuration.h"
#include "service/glrenderer/shader.h"
#include "service/glrenderer/shader_pack.h"
#include "utils/file_to_string.h"

static SDL_Window* window_;
static bool is_level_needs_renderer_;
static std::unique_ptr<GlRenderer> gl_renderer;

static std::vector<visual_world_objects::Type> visual_objects{};

namespace pep::assets::SimpleTriangleInterleaved {
static uint32_t id = 1;
using namespace gl_rendering_target;

// former TriangleObjectPureLayout
static float data[9 + 9]  // clang-format off
            /*data self*/ { 0.f,  0.5f, 0.f,	/* Top   */   1.f, 0.f, 0.f, /*Red channel*/
                            0.5f, -0.5f, 0.f,	/* Right */   0.f, 1.f, 0.f, /*Green channel*/
                            -0.5f, -0.5f, 0.f,	/* Left  */   0.f, 0.f, 1.f, /*Blue channel*/
            };
                          // clang-format on

static VertexDataPointer vdp = VertexDataPointer(id, 3, data);

static AttributePackSpecification aps[] = {
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kInterleaved,
                               attribute::Scheme::kPosition3d, nullptr,
                               6 * (GLsizei)SizeOfGlTypeByGlEnum(GL_FLOAT)),
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kInterleaved,
                               attribute::Scheme::kColorRgb,
                               (GLfloat*)(sizeof(GLfloat) * 3),
                               6 * (GLsizei)SizeOfGlTypeByGlEnum(GL_FLOAT))};

static RenderingTargetPackPointer rtpp{&vdp, aps, 1, 2};

const char* v_shader_src_path =
    "assets/shaders/demo/simple_interleaved/simple_triangle.v.glsl";
const char* f_shader_src_path =
    "assets/shaders/demo/simple_interleaved/simple_triangle.f.glsl";

}  // namespace pep::assets::SimpleTriangleInterleaved

namespace pep::assets::SimpleQuadIndexed {
static uint32_t id = 2;
using namespace gl_rendering_target;

const char* v_shader_src_path =
    "assets/shaders/demo/simple_indices/simple_tr_for_quad.v.glsl";
const char* f_shader_src_path =
    "assets/shaders/demo/simple_indices/simple_tr_for_ind_quad.f.glsl";

static GLfloat v_data[]  // clang-format off
            {
                    -0.5f,  0.5f, 0.0f,		// top left
                    0.5f,  0.5f, 0.0f,		// top right
                    0.5f, -0.5f, 0.0f,		// bottom right
                    -0.5f, -0.5f, 0.0f		// bottom left
            };

    static GLuint i_data[] = {
            0, 1, 2,  // first triangle
            0, 2, 3   // second triangle
    };
                         // clang-format on

// TODO: indices type "must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or
// GL_UNSIGNED_INT"
static VertexDataPointer vdp =
    VertexDataPointer(id, 4, v_data, 6, GL_UNSIGNED_INT, i_data);

static AttributePackSpecification aps =
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kContiguous,
                               attribute::Scheme::kPosition3d);

static RenderingTargetPackPointer rtpp{&vdp, &aps, 1, 1};

}  // namespace pep::assets::SimpleQuadIndexed

namespace pep::assets::TexturedQuad {
static uint32_t id = 3;
using namespace gl_rendering_target;

const char* v_shader_src_path = "assets/shaders/demo/texturing/texture.v.glsl";
const char* f_shader_src_path = "assets/shaders/demo/texturing/texture.f.glsl";


static GLfloat v_data[]  // clang-format off
            {
                    // position			 // tex coords
                    -0.5f,  0.5f, 0.0f,	 0.0f, 1.0f,		// top left
                    0.5f,  0.5f, 0.0f,	 1.0f, 1.0f,		// top right
                    0.5f, -0.5f, 0.0f,	 1.0f, 0.0f,		// bottom right
                    -0.5f, -0.5f, 0.0f,	 0.0f, 0.0f,		// bottom left
            };

    static GLuint i_data[] = {
            0, 1, 2,  // first triangle
            0, 2, 3   // second triangle
    };
// clang-format on

static VertexDataPointer vdp =
    VertexDataPointer(id, 4, v_data, 6, GL_UNSIGNED_INT, i_data);

static AttributePackSpecification aps[] = {
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kInterleaved,
                               attribute::Scheme::kPosition3d, nullptr,
                               5 * (GLsizei)SizeOfGlTypeByGlEnum(GL_FLOAT)),
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kInterleaved,
                               attribute::Scheme::kUvCoords2d,
                               (GLvoid*)(3 * sizeof(GLfloat)),
                               5 * (GLsizei)SizeOfGlTypeByGlEnum(GL_FLOAT))};

static RenderingTargetPackPointer rtpp{&vdp, aps, 1, 2};

}  // namespace pep::assets::TexturedQuad

void GlRendererService::Render() {
  if (!is_level_needs_renderer_) return;

  gl_renderer->RenderFrame();
  SDL_GL_SwapWindow(window_);
}

void GlRendererService::SetActiveWindow(SDL_Window* window) {
  window_ = window;
}

// TODO: NVI from std::variant for vwo or just templated class?
// NOTE: one more option: contexpr class/func for deafualt assets generation
// NOTE: one more option: static const compile time  "key-value" like in
// attribute.h
void Load(visual_world_objects::Type vwo) {
  if (std::get_if<visual_world_objects::ViewableTriangle>(&vwo) != nullptr) {
    auto& vrt = std::get<visual_world_objects::ViewableTriangle>(vwo);

    using namespace pep::assets::SimpleTriangleInterleaved;

    if (vrt.mesh.getRtpp().n_vdp == 0) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has no rendering target set! Default one is used.");
#endif
      vrt.mesh.setRtpp(rtpp);
    }

    if (vrt.mesh.getRenderingTargetType() !=
        RenderingTargetType::VertexDescribed) {
#ifdef PEP_DEBUG
      Terminal::ReportErr("Object has wrong RenderingTargetType!");
#endif
    }

    if (vrt.mesh.getShaderPack().vertex_shader == nullptr ||
        vrt.mesh.getShaderPack().vertex_shader == nullptr) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has corrupted ShaderPack. Default one is used.");
#endif
      static Shader vertex_triangle =
          Shader(ShaderType::kVertex, rtpp, v_shader_src_path);
      static Shader fragment_triangle =
          Shader(ShaderType::kFragment, rtpp, f_shader_src_path);

      const ShaderPack shader_pack{&vertex_triangle, &fragment_triangle};

      vrt.mesh.setShaderPack(shader_pack);
    }

    visual_objects.emplace_back(vrt);
  }

  if (std::get_if<visual_world_objects::ViewableQuad>(&vwo) != nullptr) {
    auto& vrt = std::get<visual_world_objects::ViewableQuad>(vwo);

    using namespace pep::assets::SimpleQuadIndexed;

    if (vrt.mesh.getRtpp().n_vdp == 0) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has no rendering target set! Default one is used.");
#endif
      vrt.mesh.setRtpp(rtpp);
    }

    if (vrt.mesh.getShaderPack().vertex_shader == nullptr ||
        vrt.mesh.getShaderPack().vertex_shader == nullptr) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has corrupted ShaderPack. Default one is used.");
#endif
      static Shader vertex_triangle =
          Shader(ShaderType::kVertex, rtpp, v_shader_src_path);
      static Shader fragment_triangle =
          Shader(ShaderType::kFragment, rtpp, f_shader_src_path);

      const ShaderPack shader_pack{&vertex_triangle, &fragment_triangle};

      vrt.mesh.setShaderPack(shader_pack);
    }

    visual_objects.emplace_back(vrt);
  }

  if (std::get_if<visual_world_objects::TexturedQuad>(&vwo) != nullptr) {
    auto& vrt = std::get<visual_world_objects::TexturedQuad>(vwo);

    using namespace pep::assets::TexturedQuad;

    if (vrt.mesh.getRtpp().n_vdp == 0) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has no rendering target set! Default one is used.");
#endif
      vrt.mesh.setRtpp(rtpp);
    }

    if (vrt.mesh.getTexture().texture_asset_path.empty()) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has no src for texture. Default one is used.");
#endif
      Texture debug{"assets/images/demo/debug_texture.png"};

      vrt.mesh.setTexture(debug);
    }

    if (vrt.mesh.getShaderPack().vertex_shader == nullptr ||
        vrt.mesh.getShaderPack().fragment_shader == nullptr) {
#ifdef PEP_DEBUG
      Terminal::ReportErr(
          "Object has corrupted ShaderPack. Default one is used.");
#endif
      static Shader vertex_tex_quad =
          Shader(ShaderType::kVertex, rtpp, v_shader_src_path);
      static Shader fragment_tex_quad =
          Shader(ShaderType::kFragment, rtpp, f_shader_src_path);

      vrt.mesh.setShaderPack({&vertex_tex_quad, &fragment_tex_quad});
    }

    if (vrt.mesh.getRenderingTargetType() ==
        RenderingTargetType::VertexDescribed) {
#ifdef PEP_DEBUG
      Terminal::ReportErr("Object has wrong RenderingTargetType!");
#endif
    }
    visual_objects.emplace_back(vrt);
  }
}

void GlRendererService::InitFor(size_t level_id) {
  gl_renderer = std::make_unique<GlRenderer>();

  auto level = (*gGameConfiguration.Levels)[level_id];

  is_level_needs_renderer_ = !level.visual_world_objects.empty();

  if (is_level_needs_renderer_) {
    for (const auto& vwo_data : level.visual_world_objects) {
      Load(vwo_data);
    }

    gl_renderer->Init(visual_objects);
  }
}

void GlRendererService::Destroy() {
  visual_objects.erase(visual_objects.begin(), visual_objects.end());
  gl_renderer.reset();
}

void GlRendererService::SwitchGlPolygonMode(GlPolygonMode mode) {
  gl_renderer->SwitchGlPolygonMode(mode);
}

void GlRendererService::SetGlClearColor(gl_color color) {
  gl_renderer->setClearColor(color);
}

gl_color GlRendererService::GetGlClearColor() {
  return gl_renderer->getClearColor();
}
