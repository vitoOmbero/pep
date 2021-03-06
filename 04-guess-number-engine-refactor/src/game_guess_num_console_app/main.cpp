#include <string>

#include "game_guess_num_console_app/assets_loader.h"
#include "engine/engine.h"
#include "utils/terminal.h"

void AtExit() { pep::AtExitMessage(); }

int main() {
  const int result = std::atexit(AtExit);

  if (result != 0) {
    Terminal::ReportErr("AtExit registration failed\n");
    return EXIT_FAILURE;
  }

  AssetsLoader::LoadStaticAssetsForGuessNumber(Culture::kEn);
  pep::Engine e;
  e.Play();

  std::exit(EXIT_SUCCESS);
}
