#ifndef ENGINELIB_LOAD_H
#define ENGINELIB_LOAD_H

#include <cstddef>
#include <cstdint>

#include "engine/libengine.h"


namespace engine_func_load::ptrs
{
using PrintHelloFromEngine  = void(*)();

}

#ifndef PTRS_ONLY
namespace engine_func_load::symbols
{

static const char* PrintHelloFromEngine  = "hello";

}
#endif

#endif