#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "engine/engine_func_load.h"
#include "game/game_func_load.h"


const char* lib_engine_name{ "libengine.so" };
void*       engine_handle;

const char* lib_game_name{ "libgame.so" };
void*       game_handle;

struct engine_loaded_ptrs{
    engine_func_load::ptrs::PrintHelloFromEngine PrintHelloFromEngine;
};

struct game_loaded_ptrs
{
    game_func_load::ptrs::PrintHelloFromGame  PrintHelloFromGame;
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

void LoadFunctions(game_loaded_ptrs& fpc /*out*/)
{
    using namespace game_func_load;

    game_handle = dlopen(lib_game_name, RTLD_LAZY);

    if (NULL == game_handle)
    {
        std::cerr << dlerror() << std::endl;
        std::terminate();
    }

    fpc.PrintHelloFromGame =
        (ptrs::PrintHelloFromGame)dlsym(game_handle, symbols::PrintHelloFromGame);
}

#ifndef DOCTEST_CONFIG_DISABLE
namespace game {
    DOCTEST_SYMBOL_IMPORT void hello_from_game();
}
namespace engine {
    DOCTEST_SYMBOL_IMPORT void hello();
}
#endif

int main(int argc, char* argv[])
{
    std::cout << "App is running!" << std::endl;
    engine_loaded_ptrs fpc_engine;
    game_loaded_ptrs fpc_game;

    LoadFunctions(fpc_engine);
    LoadFunctions(fpc_game);

    fpc_engine.PrintHelloFromEngine();
    fpc_game.PrintHelloFromGame();

    dlclose(game_handle);
    dlclose(engine_handle);

#ifndef DOCTEST_CONFIG_DISABLE

    std::cout << "<< force direct usage engine (doctest)" << std::endl;
    engine::hello();
    std::cout << "<< force direct usage game (doctest)" << std::endl;
    game::hello_from_game();

  doctest::Context context(argc, argv);
  int res = context.run();

  if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
    return res;          // propagate the result of the tests

  int client_stuff_return_code = 0;
  // your program - if the testing framework is integrated in your production code

  return res + client_stuff_return_code; // the result from doctest is propagated here as well
#else
  return 0;
#endif
}




TEST_CASE("executable") {
    printf("I am a test from the executable!\n");
}