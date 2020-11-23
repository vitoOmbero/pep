#include "engine/service/level_processing/game_level_logic_processor.h"

#include <chrono>
#include <thread>

#include "engine/configuration.h"
#include "service/event_processing/event_processing_service.h"
#include "service/game_update/game_update_service.h"
#include "service/glrenderer/gl_renderer.h"
#include "service/glrenderer/gl_renderer_service.h"
#include "service/glrenderer/mesh.h"
#include "service/text_world/game_objects.h"
#include "utils/file_to_string.h"
#include "utils/terminal.h"


namespace pep::assets::SimpleTriangleInterleaved
{
     static uint32_t id = 111;
    using namespace gl_rendering_target;

// former TriangleObjectPureLayout
     static float data[9+9] // clang-format off
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
                                       6 * (GLsizei)SizeOfGlTypeByGLenum(GL_FLOAT))
    };

     static RenderingTargetPackPointer rtpp{ &vdp, aps, 1, 2 };

     const char* v_shader_src_path =
            "assets/shaders/demo/simple_interleaved/simple_triangle.v.glsl";
     const char* f_shader_src_path =
            "assets/shaders/demo/simple_interleaved/simple_triangle.f.glsl";
} // namespace demo::assets::SimpleTriangleInterleaved


namespace pep::assets::SimpleQuadIndexed
{
     static uint32_t id = 222;
    using namespace gl_rendering_target;

     const char* v_shader_src_path =
            "assets/shaders/demo/simple_indices/simple_tr_for_quad.v.glsl";
     const char* f_shader_src_path =
            "assets/shaders/demo/simple_indices/simple_tr_for_ind_quad.f.glsl";

     static GLfloat v_data[] // clang-format off
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

     static RenderingTargetPackPointer rtpp{ &vdp, &aps, 1, 1 };

} // namespace demo::assets::SimpleQuadIndexed


void GameLevelLogicProcessor::ProcessLevel(size_t level_id) {
  current_processing_level_id_ = level_id;
  (*gGameConfiguration.Levels)[level_id].game_logic.OnLoad();

  is_continuing_ = true;

  auto timer = std::chrono::high_resolution_clock();
  auto begin = timer.now();

  // load meshes simulation
  GlRenderer gl_renderer;

  Mesh triangle(
      pep::assets::SimpleTriangleInterleaved::rtpp,
      FileToString(pep::assets::SimpleTriangleInterleaved::v_shader_src_path),
      FileToString(pep::assets::SimpleTriangleInterleaved::f_shader_src_path));

  std::vector<Mesh> meshes{triangle};

  if (level_id == 1) gl_renderer.Init(meshes);

  while (is_continuing_) {
    auto last_frame_end = timer.now();

    EventProcessingService::ProcessEvent();

    frame_delta_ = std::chrono::duration_cast<std::chrono::milliseconds>(
            last_frame_end - begin);

    if (frame_delta_.count() < 1000 % 60) {
      std::this_thread::yield();
      continue;
    }

    GameUpdateService::Update(frame_delta_);

    if (level_id == 1) GlRendererService::Render(gl_renderer);

    (*gGameConfiguration.Levels)[level_id].game_logic.ExecuteTextWorldLogic();

    (*gGameConfiguration.Levels)[level_id].game_logic.Transition();

    begin = last_frame_end;
  }
}

size_t GameLevelLogicProcessor::getCurrentProcessingLevelId() const {
  return current_processing_level_id_;
}

void GameLevelLogicProcessor::Init() {
  if (!is_inited_) {
    singleton_ = std::make_unique<GameLevelLogicProcessor>();
    is_inited_ = true;
  }
#ifdef PEP_VERBOSE_GAME_LOGIC
  else
    Terminal::ReportErr("Bad usage of GameLevelLogicProcessor singleton!");
#endif
}

GameLevelLogicProcessor &GameLevelLogicProcessor::GetSingleton() {
  if (is_inited_) {
    return *singleton_;
  } else {
#ifdef PEP_VERBOSE_GAME_LOGIC
    Terminal::ReportErr(
        "GameLevelLogicProcessor singleton is not created yet!");
    Terminal::ReportErr("It is very, very bad!");
#endif
    std::exit(EXIT_FAILURE);
  }
}

void GameLevelLogicProcessor::LoadTextWorldObject(
    size_t level_based_two_id) const {
  auto two = (*gGameConfiguration.Levels)[current_processing_level_id_]
                 .text_world_objects[level_based_two_id];
  // TODO: checks for AssetsLoader
  TextWorldObjectProcessor(current_processing_level_id_).Process(two);
}

void GameLevelLogicProcessor::BreakMainLoop() { is_continuing_ = false; }
