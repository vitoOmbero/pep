#include "service/glrenderer/gl_renderer_service.h"

#include <memory>

#include "engine/configuration.h"
#include "utils/file_to_string.h"

static SDL_Window* window_;
static bool is_level_needs_renderer_;
static std::unique_ptr<GlRenderer> gl_renderer;

static std::vector<Mesh> meshes{};

namespace pep::assets::SimpleTriangleInterleaved {
static uint32_t id = 111;
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
                               6 * (GLsizei)SizeOfGlTypeByGLenum(GL_FLOAT)),
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kInterleaved,
                               attribute::Scheme::kColorRgb,
                               (GLfloat*)(sizeof(GLfloat) * 3),
                               6 * (GLsizei)SizeOfGlTypeByGLenum(GL_FLOAT))};

static RenderingTargetPackPointer rtpp{&vdp, aps, 1, 2};

const char* v_shader_src_path =
    "assets/shaders/demo/simple_interleaved/simple_triangle.v.glsl";
const char* f_shader_src_path =
    "assets/shaders/demo/simple_interleaved/simple_triangle.f.glsl";

attribute::Type attribute_location_scheme[]{attribute::Type::kPosition,
                                            attribute::Type::kColor};

static ShaderPack shader_pack{FileToString(v_shader_src_path),
                              FileToString(f_shader_src_path), 2,
                              attribute_location_scheme};

}  // namespace pep::assets::SimpleTriangleInterleaved

namespace pep::assets::SimpleQuadIndexed {
static uint32_t id = 222;
using namespace gl_rendering_target;

const char* v_shader_src_path =
    "assets/shaders/demo/simple_indices/simple_tr_for_quad.v.glsl";
const char* f_shader_src_path =
    "assets/shaders/demo/simple_indices/simple_tr_for_ind_quad.f.glsl";

static GLfloat v_data[]  // clang-format off
            /*data self*/ {
                    -0.5f,  0.5f, 0.0f,		// Top left
                    0.5f,  0.5f, 0.0f,		// Top right
                    0.5f, -0.5f, 0.0f,		// Bottom right
                    -0.5f, -0.5f, 0.0f		// Bottom left
            };

    static GLuint i_data[] = {
            0, 1, 2,  // First Triangle
            0, 2, 3   // Second Triangle
    };
                         // clang-format on

static VertexDataPointer vdp =
    VertexDataPointer(id, 4, v_data, 6, GL_UNSIGNED_INT, i_data);

static AttributePackSpecification aps =
    AttributePackSpecification(id, GL_FLOAT, AttributeDataLayout::kContiguous,
                               attribute::Scheme::kPosition3d);

static RenderingTargetPackPointer rtpp{&vdp, &aps, 1, 1};

attribute::Type attribute_location_scheme[]{attribute::Type::kPosition};

static ShaderPack shader_pack{FileToString(v_shader_src_path),
                              FileToString(f_shader_src_path), 1,
                              attribute_location_scheme};

}  // namespace pep::assets::SimpleQuadIndexed

void GlRendererService::Render() {
  if (!is_level_needs_renderer_) return;

  gl_renderer->RenderFrame();
  SDL_GL_SwapWindow(window_);
}

void GlRendererService::SetActiveWindow(SDL_Window* window) {
  window_ = window;
}

void LoadMesh(visual_world_objects::Type vwo) {
  if (std::get_if<visual_world_objects::Viewable>(&vwo) != nullptr) {
    auto vrt = std::get<visual_world_objects::Viewable>(vwo);

    if (vrt.mesh.getRtpp().n_vdp == 0) {
      using namespace pep::assets::SimpleTriangleInterleaved;
      ShaderPack sp{FileToString(v_shader_src_path),
                    FileToString(f_shader_src_path), 2,
                    attribute_location_scheme};
      meshes.emplace_back(rtpp, RenderingTargetType::VertexDescribed, sp);
    }
  }
}

void GlRendererService::InitFor(size_t level_id) {
  gl_renderer = std::make_unique<GlRenderer>();

  auto level = (*gGameConfiguration.Levels)[level_id];

  is_level_needs_renderer_ = !level.visual_world_objects.empty();

  if (is_level_needs_renderer_) {
    // TODO: mesh load
    for (auto vwo_data : level.visual_world_objects) {
      LoadMesh(vwo_data);
    }

    gl_renderer->Init(meshes);
  }
}

void GlRendererService::Destroy() {
  meshes.erase(meshes.begin(), meshes.end());
  gl_renderer.reset();
}