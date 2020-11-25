#ifndef INC_05_GUESS_NUMBER_KEYS_H
#define INC_05_GUESS_NUMBER_KEYS_H



#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// NOTE: implicitly used in current code
enum class Scope {
  kWindow,  // <--- right now only one is possible
  kRectangularZone,
};

using binding_temp = std::pair<std::string, std::string>;

using input_handler_t = void (*)();

enum class KeyName {
  // letters
  kQ,
  kW,
  kE,
  kR,
  kT,
  kY,
  kU,
  kI,
  kO,
  kP,
  kA,
  kS,
  kD,
  kF,
  kG,
  kH,
  kJ,
  kK,
  kL,
  kZ,
  kX,
  kC,
  kV,
  kB,
  kN,
  kM,
  //

  // numbers
  k0,
  k1,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  //

  // support
  kBackquote,
  kMinus,
  kEquals,
  //

  // special
  kEsc,
  kTab,
  // kCtrl,
  kCtrlLeft,
  kCtrlRight,
  kSpace,
  kCapsLk,
  // kAlt,
  kAltLeft,
  kAltRight,
  kEnter,
  // kShift,
  kShiftLeft,
  kShiftRight,
  kBackSpace,
  kDelete,
  kInsert,
  kPrtSc,
  kHome,
  kEnd,
  kPgUp,
  kPgDn,

  // arrows
  kArrowLeft,
  kArrowRight,
  kArrowUp,
  kArrowDown,
  //
};



enum class MouseKeyName {
  kMouseButtonLeft,
  kMouseButtonMid,
  kMouseButtonRight,
  kMouseWheelScrollUp,
  kMouseWheelScrollDown
};

enum class MouseActionName { kClick, kDoubleClick, kBothButtonClick, kDrag };

enum class TouchActionName { kTap, kDoubleTap, kSwipe };

using KeyMap = std::unordered_map<KeyName, input_handler_t>;
using MouseMap = std::unordered_map<MouseActionName, input_handler_t>;
using TouchMap = std::unordered_map<TouchActionName, input_handler_t>;

struct InputMode {
  KeyMap key_map{};
  MouseMap mouse_map{};
  TouchMap touch_map{};
};

using InputModeVector = std::vector<InputMode>;

#endif  // INC_05_GUESS_NUMBER_KEYS_H
