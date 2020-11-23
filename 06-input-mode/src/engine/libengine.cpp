#include "engine/libengine.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#pragma clang diagnostic pop
#ifdef PEP_BUILD_TESTS
#include "doctest.h"
#endif
#ifdef PEP_BUILD_TESTS
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#endif
#include <iostream>
#ifdef PEP_BUILD_TESTS
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END
#endif

#include <SDL2/SDL.h>

#include "engine/service/level_processing/game_level_logic_processor.h"
#include "engine/service/variable_processing/template_string_processing.h"
#include "engine/service/glrenderer/gl_renderer_service.h"
#include "engine/symbol_export.h"
#include "utils/terminal.h"
#include "version.h"

namespace engine {

static std::string at_exit_message;

PEP_DECLSPEC void hello() {
  std::cout << "Hello from engine!" << std::endl;
  SDL_version compiled = {0, 0, 0};
  SDL_version linked = {0, 0, 0};

  SDL_VERSION(&compiled)
  SDL_GetVersion(&linked);

  std::cout << "SDL2 version: " << linked << std::endl;
  std::cout << "Engine version: " << EngineVersion << std::endl;

  if (SDL_COMPILEDVERSION !=
      SDL_VERSIONNUM(linked.major, linked.minor, linked.patch)) {
    std::cerr << "warning: SDL2 compiled and linked version mismatch: "
              << compiled << " " << linked << std::endl;
  }

  const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
  if (init_result != 0) {
    auto err_message = SDL_GetError();
    std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
  }
}

PEP_DECLSPEC [[maybe_unused]] void AtExit() {
  if (!at_exit_message.empty())
    Terminal::PrintBorderedText('+', at_exit_message);
}

PEP_DECLSPEC [[maybe_unused]] void Configure(EngineConfiguration cfg) {
  gEngineConfiguration = cfg;

#ifdef PEP_DEBUG
  std::cout << "Engine is configured with: " << cfg.placeholder << std::endl;
#endif

  Terminal::Init();

  /// TODO: stopped
}

PEP_DECLSPEC [[maybe_unused]] void SetGameConfiguration(GameConfiguration cfg) {
  gGameConfiguration = cfg;

  at_exit_message =
      gGameConfiguration.DescriptionStrings->at(gGameConfiguration.Language)
          .bye_bye_msg;

#ifdef PEP_DEBUG
  Terminal::ReportErr(cfg.DescriptionInfo->project_work_name);

  Terminal::ReportErr((void *)cfg.DescriptionInfo);
  Terminal::ReportErr((void *)cfg.DescriptionStrings);
  Terminal::ReportErr((void *)cfg.StringAssets);
  Terminal::ReportErr((void *)cfg.GlobalVariableDeclarations);
  Terminal::ReportErr((void *)cfg.Levels);
#endif

  GameVariablesService::global_vars.Add(
      *(gGameConfiguration.GlobalVariableDeclarations));

  GameLevelLogicProcessor::Init();
}

PEP_DECLSPEC [[maybe_unused]] void Play() {
  const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
  if (init_result != 0) {
    const char *err_message = SDL_GetError();
    std::cerr << "error: failed call SDL_Init: " << err_message << std::endl;
    std::terminate();
  }


  int result;

  // configure opengl
  int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#ifdef PEP_DEBUG
  context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
  result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
  SDL_assert(result == 0);
  result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                               SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_assert(result == 0);
  result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_assert(result == 0);
  result = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_assert(result == 0);
  /*
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
   */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


  int gl_major_ver = 0;
  int gl_minor_ver = 0;



  result = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major_ver);
  SDL_assert(result == 0);
  result = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor_ver);
  SDL_assert(result == 0);

  SDL_Window *const window =
      SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, ::SDL_WINDOW_OPENGL);

  if (window == nullptr) {
    std::string msg{">> engine error >> failed call SDL_CreateWindow: "};
    msg += SDL_GetError();
    Terminal::ReportErr(msg);
    SDL_Quit();
    std::terminate();
  }

  auto gl_context = SDL_GL_CreateContext(window);

  if (gl_context == nullptr) {
    std::string msg(">> engine error >> can't create opengl context: ");
    msg += SDL_GetError();
    Terminal::ReportErr(msg);
    SDL_Quit();
    std::terminate();
  }

  result = SDL_GL_MakeCurrent(window, gl_context);
  SDL_assert(result == 0);


  // init glad
  if(!gladLoadGL()) {
    Terminal::ReportErr("Something went wrong!");
  }
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    Terminal::ReportErr("Failed to initialize GLAD");
  }


#ifdef PEP_DEBUG
  Terminal::ReportMsg("OpenGL Version: ");
  Terminal::ReportMsg(std::to_string(GLVersion.major));
  Terminal::ReportMsg(std::to_string(GLVersion.minor));

  Terminal::ReportMsg("OpenGL Shading Language Version: ");
  std::cout << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  Terminal::ReportMsg("OpenGL Vendor: ");
  Terminal::ReportMsg((char *)glGetString(GL_VENDOR));

  Terminal::ReportMsg("OpenGL Renderer: ");
  Terminal::ReportMsg((char *)glGetString(GL_RENDERER));
#endif

#ifdef PEP_DEBUG
  Terminal::ReportMsg("OpenGL Version: ");
  Terminal::ReportMsg(std::to_string(gl_major_ver));
  Terminal::ReportMsg(std::to_string(gl_minor_ver));
#endif

#ifdef PEP_DEBUG
  Terminal::ReportMsg("Engine play() called...");
#endif
  GlRendererService::SetActiveWindow(window);

  GameLevelLogicProcessor::GetSingleton().ProcessLevel(
      gGameConfiguration.DescriptionInfo->entry_point);

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

}  // namespace engine

#ifdef PEP_BUILD_TESTS
TEST_CASE("engine") { printf("I am a test from the engine!\n"); }
#endif