#ifndef TERMINAL_H
#define TERMINAL_H

#include <string_view>

/*!
 * NOTE: Current realization just demonstrates an idea, there are no real work
 * with unicode and no correct layout
 */
class Terminal {
 public:
  static void Init() {
    if (!is_inited)
      // NOTE: class has no state yet
      Terminal();
    else
      ReportErr("Terminal is already initialized.");
  };

  static void PrintBorderedText(char filler, std::string_view msg);

  static void ReportErr(std::string_view msg);

  static void ReportErr(void *msg);

  static void ReportMsg(std::string_view msg);

  static void ReportVal(std::string_view msg, size_t val);

  static void ReportVal(std::string_view msg, size_t val,
                        std::string_view msg2);

  static void InputValue(std::string_view msg_tip, std::string_view msg_fail,
                         size_t &val_storage, size_t min, size_t max);

  static void ReportTip(std::string_view tip);

  static void PressAnyKeyToContinue(std::string_view tip);

  static void PrintText(std::string_view basic_string);

 private:
  Terminal();

  inline static bool is_inited = false;
  inline static const int WIDTH = 50;
  inline static const int BAD_INPUT_TRIES_MAX = 5;
};

#endif  // TERMINAL_H
