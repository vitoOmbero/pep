#ifndef INC_05_GUESS_NUMBER_COLOR_MAP_H
#define INC_05_GUESS_NUMBER_COLOR_MAP_H

#include <map>

#include "color.h"
#include "rgb888.h"

namespace ColorMap {

Color FindColor(Rgb888 rgb);
Rgb888 FindRgbCode(Color colorName);
Color FindClosestColor(Rgb888 rgb);

}  // namespace ColorMap

#endif  // INC_05_GUESS_NUMBER_COLOR_MAP_H
