#include "engine/libengine.h"

#define DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <iostream>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "include/engine/symbol_export.h"

namespace engine{

  MANGLING void hello() {
    std::cout << "Hello from engine!" << std::endl;
  }

}

TEST_CASE("engine") {
  printf("I am a test from the engine!\n");
}