#include "game/libgame.h"

#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "engine/engine_func_load.h"
#include "include/game/symbol_export.h"

const char* lib_engine_name{ "libengine.so" };
void*       engine_handle;

struct engine_loaded_ptrs{
    engine_func_load::ptrs::PrintHelloFromEngine PrintHelloFromEngine;
};

void LoadFunctions(engine_loaded_ptrs& fpc /*out*/)
{
    using namespace engine_func_load;

    engine_handle = dlopen(lib_engine_name, RTLD_LAZY);

    if (NULL == engine_handle)
    {
        std::cerr << dlerror() << std::endl;
        std::terminate();
    }

    fpc.PrintHelloFromEngine =
        (ptrs::PrintHelloFromEngine)dlsym(engine_handle, symbols::PrintHelloFromEngine);
}

namespace game{

  MANGLING [[maybe_unused]] void hello_from_game() {
    std::cout << "Hello from game!" << std::endl;
    std::cout << "Game uses engine: ";
    engine_loaded_ptrs fpc;
    LoadFunctions(fpc);
    fpc.PrintHelloFromEngine();
  }

}



TEST_CASE("game") {
    printf("I am a test from the game!\n");
}