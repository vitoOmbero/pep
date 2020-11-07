#include "utils/terminal.h"

#include <iomanip>
#include <iostream>

Terminal::Terminal() {
  std::ostringstream oss;
  // iss.imbue(std::locale("en_US.UTF8"));
  // oss.imbue(std::locale("ru_RU.UTF-8"));
  std::cout << "Current locale: " << oss.getloc().name() << '\n';
}

void Terminal::ReportErr(std::string_view msg) {
  std::cerr << msg << std::endl;
}

void Terminal::ReportErr(void *msg) { std::cerr << msg << std::endl; }

void Terminal::ReportMsg(std::string_view msg) {
  std::cout << msg << std::endl;
  std::cout.flush();
}

void Terminal::PrintBorderedText(const char filler, std::string_view msg) {
  auto Line = [filler]() {
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout.fill(filler);
    std::cout << std::setw(WIDTH) << filler << std::endl;
  };
  auto Empty = [filler]() {
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout.fill(L' ');
    std::cout << filler << std::setw(WIDTH - 1) << filler << std::endl;
  };

  auto Text = [filler](std::string_view msg) {
    if (msg.length() > WIDTH - 4)
      std::cout << filler << ' ' << msg.substr(0, 46) << ' ' << filler
                << std::endl;
    else {
      const auto shift = msg.length() % 2 == 1 ? 1 : 0;
      std::cout.fill(L' ');
      auto empty = WIDTH / 2 - shift - msg.length() / 2;
      std::cout.setf(std::ios::left, std::ios::adjustfield);
      std::cout << std::setw(empty) << filler;
      std::cout << msg;
      std::cout.setf(std::ios::right, std::ios::adjustfield);
      std::cout << std::setw(static_cast<int>(empty + shift)) << filler;
      std::cout << std::endl;
    }
  };

  Line();
  Empty();
  Text(msg);
  Empty();
  Line();
}

void Terminal::ReportVal(std::string_view msg, size_t val) {
  std::cout << msg << val << std::endl;
}

void Terminal::ReportVal(std::string_view msg, size_t val,
                         std::string_view msg2) {
  std::cout << msg << val << msg2 << std::endl;
}

void Terminal::InputValue(std::string_view msg_tip, std::string_view msg_fail,
                          size_t &val_storage, size_t min, size_t max) {
  int tries = 0;
  while (true) {
    Terminal::ReportTip(msg_tip);
    std::cin >> val_storage;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(PTRDIFF_MAX - 1, '\n');
      Terminal::ReportMsg(msg_fail);
      ++tries;
    } else {
      if (val_storage > max || val_storage < min) {
        Terminal::ReportMsg(msg_fail);
        ++tries;
        continue;
      }
      std::cin.ignore(PTRDIFF_MAX - 1, '\n');
      return;
    }

    if (tries >= Terminal::BAD_INPUT_TRIES_MAX) {
      Terminal::ReportMsg(msg_fail);
      Terminal::ReportMsg(msg_tip);
      Terminal::ReportMsg(std::to_string(min));
      val_storage = min;
      return;
    }
  }
}

void Terminal::ReportTip(std::string_view tip) { std::cout << tip; }

void Terminal::PressAnyKeyToContinue(std::string_view tip) {
  std::cout << tip;
  std::cin.get();
  // win system("pause")
}

void Terminal::PrintText(std::string_view msg) {
  std::cout << msg << std::endl;
}
