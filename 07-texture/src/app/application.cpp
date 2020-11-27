#include "application.h"

#include "fpc.h"

void Application::Run() {
  _assets_loader.LoadStaticAssets();

  EngineConfiguration cfg;
  engine_fpc::Get().Configure(cfg);

  GameConfiguration game_cfg{_assets_loader.getDescriptionInfo(),
                             _assets_loader.getDescriptionStrings(),
                             _assets_loader.getStringAssets(),
                             _assets_loader.getGlobalVariableDeclarations(),
                             _assets_loader.getLevels(),
                             _assets_loader.getLanguage(),
                             _assets_loader.getInputModes(),
                             _assets_loader.getTexturePackMap()};

  engine_fpc::Get().SetGameConfiguration(game_cfg);

  engine_fpc::Get().Play();
}

Application::Application() {}
