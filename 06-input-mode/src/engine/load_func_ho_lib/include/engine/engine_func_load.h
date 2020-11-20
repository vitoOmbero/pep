#ifndef ENGINE_LIB_LOAD_H
#define ENGINE_LIB_LOAD_H

#include <dlfcn.h>

#include <cstddef>
#include <cstdint>
#include <iostream>

#include "engine/libengine.h"

namespace engine_func_load::ptrs {
using PrintHelloFromEngine = void (*)();
using AtExit = void (*)();
using Configure = void (*)(EngineConfiguration cfg);
using SetGameConfiguration = void (*)(GameConfiguration cfg);
using Play = void (*)();
}  // namespace engine_func_load::ptrs

#ifndef PTRS_ONLY
namespace engine_func_load::symbols {

static const char *PrintHelloFromEngine = "hello";
static const char *AtExit = "AtExit";
static const char *Configure = "Configure";
static const char *SetGameConfiguration = "SetGameConfiguration";
static const char *Play = "Play";

}  // namespace engine_func_load::symbols
#endif

inline static const char *lib_engine_name{"libengine.so"};
inline static void *engine_handle;

struct engine_loaded_ptrs {
  engine_func_load::ptrs::PrintHelloFromEngine PrintHelloFromEngine;
  engine_func_load::ptrs::AtExit AtExit;
  engine_func_load::ptrs::Configure Configure;
  engine_func_load::ptrs::SetGameConfiguration SetGameConfiguration;
  engine_func_load::ptrs::Play Play;
};

inline static void LoadFunctions(engine_loaded_ptrs &fpc /*out*/) {
  using namespace engine_func_load;

  engine_handle = dlopen(lib_engine_name, RTLD_LAZY);

  if (nullptr == engine_handle) {
    std::cerr << dlerror() << std::endl;
    std::terminate();
  }

  fpc.PrintHelloFromEngine = (ptrs::PrintHelloFromEngine)dlsym(
      engine_handle, symbols::PrintHelloFromEngine);
  fpc.AtExit = (ptrs::AtExit)dlsym(engine_handle, symbols::AtExit);
  fpc.Configure = (ptrs::Configure)dlsym(engine_handle, symbols::Configure);
  fpc.SetGameConfiguration = (ptrs::SetGameConfiguration)dlsym(
      engine_handle, symbols::SetGameConfiguration);
  fpc.Play = (ptrs::Play)dlsym(engine_handle, symbols::Play);
}

#endif