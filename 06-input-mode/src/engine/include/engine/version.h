//
// Created by vito on 12.11.20.
//

#ifndef INC_05_GUESS_NUMBER_VERSION_H
#define INC_05_GUESS_NUMBER_VERSION_H

#include <cassert>
#include <iostream>

#ifndef PEP_VERSION_MAJOR
static_assert(1 == 0, "PEP_VERSION_MAJOR is undefined!");
#endif
#ifndef PEP_VERSION_MINOR
static_assert(1 == 0, "PEP_VERSION_MINOR is undefined!");
#endif
#ifndef PEP_VERSION_PATCH
static_assert(1 == 0, "PEP_VERSION_PATCH is undefined!");
#endif

#include <SDL_version.h>

struct PepVersion {
  [[nodiscard]] uint8_t getMajor() const { return version_.major; }
  [[nodiscard]] uint8_t getMinor() const { return version_.minor; }
  [[nodiscard]] uint8_t getPatch() const { return version_.patch; }

 private:
#define SET_VERSION_AT_COMPILE_TIME(maj, min, pat) \
  { maj min pat }

  SDL_version version_ = SET_VERSION_AT_COMPILE_TIME(
      PEP_VERSION_MAJOR, PEP_VERSION_MINOR, PEP_VERSION_PATCH);

  friend std::ostream& operator<<(std::ostream& out, const PepVersion& v);
};

inline std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
  out << static_cast<int>(v.major) << '.';
  out << static_cast<int>(v.minor) << '.';
  out << static_cast<int>(v.patch);
  return out;
}

inline std::ostream& operator<<(std::ostream& out, const PepVersion& v)
{
  out << v.version_;
  return out;
}

inline static PepVersion EngineVersion{};

#endif  // INC_05_GUESS_NUMBER_VERSION_H
