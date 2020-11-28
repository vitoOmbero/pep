#ifndef INC_05_GUESS_NUMBER_GAME_UPDATE_SERVICE_H
#define INC_05_GUESS_NUMBER_GAME_UPDATE_SERVICE_H

#include <chrono>
#include <iostream>

#include "utils/terminal.h"

namespace GameUpdateService {

inline void Update(std::chrono::milliseconds frame_delta) {
  // std::cout << "frame_delta (ms)" << frame_delta.count() << std::endl;
};

}  // namespace GameUpdateService

#endif  // INC_05_GUESS_NUMBER_GAME_UPDATE_SERVICE_H
