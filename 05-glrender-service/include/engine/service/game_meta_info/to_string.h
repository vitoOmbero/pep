//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_TO_STRING_H
#define INC_01_GUESS_NUMBER_PROTO_TO_STRING_H

#include <sstream>
#include <string>

#include "engine/engine_assets.h"
#include "version.h"

static std::string ToString(Version ver,
                            Culture::Language lang = Culture::kEn) {
  std::ostringstream oss;
  oss << Culture::strings.at(lang).description_strings.version << " "
      << std::to_string(ver.major) << "." << std::to_string(ver.minor) << "."
      << std::to_string(ver.patch);
  return oss.str();
}

#endif  // INC_01_GUESS_NUMBER_PROTO_TO_STRING_H
