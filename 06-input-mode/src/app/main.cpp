#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#pragma clang diagnostic pop

#include "doctest.h"

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <dlfcn.h>

#include <cassert>
#include <iostream>

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "application.h"
#include "fpc.h"

#ifndef DOCTEST_CONFIG_DISABLE
namespace game {
DOCTEST_SYMBOL_IMPORT void
hello_from_game();  // NOLINT(readability-redundant-declaration)
}
namespace engine {
DOCTEST_SYMBOL_IMPORT void
hello();  // NOLINT(readability-redundant-declaration)
}
#endif

void ExecuteWorkflow() {
  Application linux_app;
  linux_app.Run();
}

void AtExit() {
  engine_fpc::Get().AtExit();
  dlclose(game_handle);
  dlclose(engine_handle);
}

int main(int argc, char *argv[]) {
#ifdef PEP_DEBUG
  if (argc > 1) {
    return EXIT_SUCCESS;
  }
#endif

  std::cout << "App is running!" << std::endl;
  engine_loaded_ptrs fpc_engine{};
  game_loaded_ptrs fpc_game{};

  LoadFunctions(fpc_engine);
  LoadFunctions(fpc_game);

  fpc_engine.PrintHelloFromEngine();
  fpc_game.PrintHelloFromGame();

#ifndef DOCTEST_CONFIG_DISABLE

  std::cout << "<< force direct usage engine (doctest)" << std::endl;
  engine::hello();
  std::cout << "<< force direct usage game (doctest)" << std::endl;
  game::hello_from_game();

  doctest::Context context(argc, argv);
  int res = context.run();

  if (context.shouldExit())  // important - query flags (and --exit) rely on
    // the user doing this
    std::exit(res);  // propagate the result of the tests
#endif

  game_fpc::Init(fpc_game);
  engine_fpc::Init(fpc_engine);

  const int result = std::atexit(AtExit);
  if (result != 0) {
    std::cerr << "AtExit registration failed" << std::endl;
    return EXIT_FAILURE;
  }

#ifdef PEP_DEBUG
  assert(game_fpc::IsInited());
  assert(engine_fpc::IsInited());
#endif

  ExecuteWorkflow();

#ifndef DOCTEST_CONFIG_DISABLE
  // G_DISABLE
  std::exit(res + EXIT_SUCCESS);
#else
  std::exit(EXIT_SUCCESS);
#endif
}

TEST_CASE("executable") { printf("I am a test from the executable!\n"); }

TEST_CASE("static function pointers are not inited") {
  CHECK(game_fpc::IsInited() == false);
  CHECK(engine_fpc::IsInited() == false);
}
