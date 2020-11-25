#include "engine/utils/color_map.h"

#include <algorithm>

namespace {

using namespace ColorMap;

static const std::map<Color, Rgb888> color_map_ = {
    {Color::kBlack, Rgb888(0, 0, 0)},
    {Color::kNavy, Rgb888(0, 0, 128)},
    {Color::kBlue, Rgb888(0, 0, 255)},
    {Color::kGreen, Rgb888(0, 128, 0)},
    {Color::kTeal, Rgb888(0, 128, 128)},
    {Color::kBlueLight, Rgb888(0, 128, 255)},
    {Color::kLime, Rgb888{0, 255, 0}},
    {Color::kGreenSpringB, Rgb888{0, 255, 128}},
    {Color::kCyan, Rgb888{0, 255, 255}},
    {Color::kIndigo, Rgb888{75, 0, 130}},
    {Color::kMaroon, Rgb888{128, 0, 0}},
    {Color::kPurple, Rgb888{128, 0, 128}},
    {Color::kPurpleBlue, Rgb888{128, 0, 255}},
    {Color::kOlive, Rgb888{128, 128, 0}},
    {Color::kGray, Rgb888{128, 128, 128}},
    {Color::kSkyBlueDark, Rgb888{128, 128, 255}},
    {Color::kSilver, Rgb888{192, 192, 192}},
    {Color::kViolet, Rgb888{238, 130, 238}},
    {Color::kRed, Rgb888{255, 0, 0}},
    {Color::kFuchsiaDark, Rgb888{255, 0, 128}},
    {Color::kMagenta, Rgb888{255, 0, 255}},
    {Color::kDarkOrange1B, Rgb888{255, 128, 0}},
    {Color::kOrange, Rgb888{255, 165, 0}},
    {Color::kCoralLightD, Rgb888{255, 128, 128}},
    {Color::kOrchid1L, Rgb888{255, 128, 255}},
    {Color::kYellow, Rgb888{255, 255, 0}},
    {Color::kKhaki1L, Rgb888{255, 255, 128}},
    {Color::kWhite, Rgb888{255, 255, 255}}};
}  // namespace

Color ColorMap::FindColor(Rgb888 rgb) {

  auto findResult =
          std::find_if(color_map_.begin(), color_map_.end(),
                       [&rgb](const std::pair<Color, Rgb888>& pair) {
                           return pair.second == rgb;
                       });

  if (findResult != std::end(color_map_))
  {
    return findResult->first;
  }
  else
  {
    return Color::kNo;
  }
}

Rgb888 ColorMap::FindRgbCode(Color colorName) {
  auto findResult =
          std::find_if(color_map_.begin(), color_map_.end(),
                       [&colorName](const std::pair<Color, Rgb888>& pair) {
                           return pair.first == colorName;
                       });

  if (findResult != std::end(color_map_))
  {
    return findResult->second;
  }
  else
  {
    return Rgb888();
  }
}

Color ColorMap::FindClosestColor(Rgb888 rgb) {
  auto findResult =
          std::find_if(color_map_.begin(), color_map_.end(),
                       [&rgb](const std::pair<Color, Rgb888>& pair) {
                           return pair.second == rgb;
                       });

  if (findResult != std::end(color_map_))
  {
    return findResult->first;
  }
  else
  {
    std::map<Color, Rgb888> potentials;

    for (auto pair : color_map_)
    {
      potentials.insert(std::pair(pair.first, (rgb - pair.second)));
    }

    auto closest =
            std::min_element(potentials.begin(), potentials.end(),
                             [](const std::pair<Color, Rgb888>& pair_left,
                                const std::pair<Color, Rgb888>& pair_right) {
                                 return pair_left.second < pair_right.second;
                             });
    return closest->first;
  }
}
