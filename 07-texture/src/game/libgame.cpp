#include "libgame.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#pragma clang diagnostic pop
#include "doctest.h"
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "engine/engine_func_load.h"
#include "symbol_export.h"

namespace game{

  PEP_DECLSPEC [[maybe_unused]] void hello_from_game() {
    std::cout << "!!! Hello from game!" << std::endl;
    std::cout << "!!! Game uses engine: ";
    engine_loaded_ptrs fpc{};
    LoadFunctions(fpc);
    fpc.PrintHelloFromEngine();
  }

}


TEST_CASE("game") {
    printf("I am a test from the game!\n");
}
