#ifndef ENGINE_LIBRARY_H
#define ENGINE_LIBRARY_H

#include "configuration.h"
#include "symbol_export.h"

namespace engine {

PEP_DECLSPEC void hello();
PEP_DECLSPEC [[maybe_unused]] void AtExit();
PEP_DECLSPEC [[maybe_unused]] void Configure(EngineConfiguration cfg);
PEP_DECLSPEC [[maybe_unused]] void SetGameConfiguration(GameConfiguration cfg);
PEP_DECLSPEC [[maybe_unused]] void Play();

}  // namespace engine

#endif  // ENGINE_LIBRARY_H
