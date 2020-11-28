#ifndef INC_05_GUESS_NUMBER_PEP_FUNC_LOAD_H
#define INC_05_GUESS_NUMBER_PEP_FUNC_LOAD_H

#include <dlfcn.h>

#include "engine/engine_func_load.h"
#include "pep.h"

// NOTE: there is no need really to export symbols until engine and game share
// one build pipeline

namespace pep_func_load::ptrs {
using GetUniformRandomNaturalNumber = size_t (*)(size_t max);

using LoadTextWorldObjectById = void (*)(pep::index i);
using DoNothing = void (*)();
using LoadLevelById = void (*)(pep::index i);
using VarNatural = size_t &(*)(const std::string &name);
using VarBool = bool &(*)(const std::string &name);
using Log2FromNatural = size_t (*)(const std::string &name);
using NewRandomNatural = size_t (*)(size_t max_value);
using SetVarNaturalInterval = void (*)(const game_var_name &interval,
                                       const game_var_name &natural_min,
                                       const game_var_name &natural_max);
}  // namespace pep_func_load::ptrs

#ifndef PTRS_ONLY
namespace pep_func_load::symbols {

static const char *GetUniformRandomNaturalNumber =
    "GetUniformRandomNaturalNumber";
static const char *LoadTextWorldObjectById = "LoadTextWorldObjectById";
static const char *DoNothing = "DoNothing";
static const char *LoadLevelById = "LoadLevelById";

static const char *VarNatural = "VarNatural";
static const char *VarBool = "VarBool";
static const char *Log2FromNatural = "Log2FromNatural";
static const char *NewRandomNatural = "NewRandomNatural";
static const char *SetVarNaturalInterval = "SetVarNaturalInterval";

}  // namespace pep_func_load::symbols
#endif

struct pep_loaded_ptrs {
  pep_func_load::ptrs::GetUniformRandomNaturalNumber
      GetUniformRandomNaturalNumber;
  pep_func_load::ptrs::LoadTextWorldObjectById LoadTextWorldObjectById;
  pep_func_load::ptrs::DoNothing DoNothing;
  pep_func_load::ptrs::LoadLevelById LoadLevelById;

  pep_func_load::ptrs::VarNatural VarNatural;
  pep_func_load::ptrs::VarBool VarBool;
  pep_func_load::ptrs::Log2FromNatural Log2FromNatural;
  pep_func_load::ptrs::NewRandomNatural NewRandomNatural;
  pep_func_load::ptrs::SetVarNaturalInterval SetVarNaturalInterval;
};

inline static void LoadFunctions(pep_loaded_ptrs &fpc /*out*/) {
  using namespace pep_func_load;

  engine_handle = dlopen(lib_engine_name, RTLD_LAZY);

  if (nullptr == engine_handle) {
    std::cerr << dlerror() << std::endl;
    std::terminate();
  }

  fpc.GetUniformRandomNaturalNumber =
      (ptrs::GetUniformRandomNaturalNumber)dlsym(
          engine_handle, symbols::GetUniformRandomNaturalNumber);
  fpc.LoadTextWorldObjectById = (ptrs::LoadTextWorldObjectById)dlsym(
      engine_handle, symbols::LoadTextWorldObjectById);
  fpc.DoNothing = (ptrs::DoNothing)dlsym(engine_handle, symbols::DoNothing);
  fpc.LoadLevelById =
      (ptrs::LoadLevelById)dlsym(engine_handle, symbols::LoadLevelById);
  fpc.VarNatural = (ptrs::VarNatural)dlsym(engine_handle, symbols::VarNatural);
  fpc.VarBool = (ptrs::VarBool)dlsym(engine_handle, symbols::VarBool);
  fpc.Log2FromNatural =
      (ptrs::Log2FromNatural)dlsym(engine_handle, symbols::Log2FromNatural);
  fpc.NewRandomNatural =
      (ptrs::NewRandomNatural)dlsym(engine_handle, symbols::NewRandomNatural);
  fpc.SetVarNaturalInterval = (ptrs::SetVarNaturalInterval)dlsym(
      engine_handle, symbols::SetVarNaturalInterval);
}

#endif  // INC_05_GUESS_NUMBER_PEP_FUNC_LOAD_H
