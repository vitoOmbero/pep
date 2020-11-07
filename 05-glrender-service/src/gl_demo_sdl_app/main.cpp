#include <string>
#include <iostream>

#include "engine/engine.h"
#include "utils/terminal.h"

#include "SDL_version.h"

void AtExit() { pep::AtExitMessage(); }

std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
  out << static_cast<int>(v.major) << '.';
  out << static_cast<int>(v.minor) << '.';
  out << static_cast<int>(v.patch);
  return out;
}

int main() {
  int result = std::atexit(AtExit);

  if (result != 0) {
    Terminal::ReportErr("AtExit registration failed\n");
    return EXIT_FAILURE;
  }

  SDL_version compiled = { 0, 0, 0 };
  SDL_version linked   = { 0, 0, 0 };

  SDL_VERSION(&compiled)
  SDL_GetVersion(&linked);

  std::cout << "compiled: " << compiled << '\n';
  std::cout << "linked: " << linked << std::endl;

  bool is_good = std::cout.good();

  result = is_good ? EXIT_SUCCESS : EXIT_FAILURE;
  return result;

  std::exit(EXIT_SUCCESS);
}
