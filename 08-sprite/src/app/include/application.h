#ifndef INC_05_GUESS_NUMBER_APPLICATION_H
#define INC_05_GUESS_NUMBER_APPLICATION_H

#include "assets_loader.h"

class Application {
 public:
  Application();

  void Run();

 private:
  AssetsLoader _assets_loader = AssetsLoader(AssetsLoadingStrategy::kCompileTimeBuiltInAssets);
};

#endif  // INC_05_GUESS_NUMBER_APPLICATION_H
