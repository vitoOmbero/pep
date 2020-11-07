//
// Created by vito on 29.10.20.
//

#include "engine/engine.h"

#include "utils/terminal.h"

void pep::AtExitMessage() {
  if (!Engine::at_exit_message.empty())
    Terminal::PrintBorderedText('+', Engine::at_exit_message);
}

pep::Engine::Engine() {
  if (!is_inited) {
    singleton_ = this;
#ifdef PEP_DEBUG
    Terminal::ReportErr("Bye msg:");
    Terminal::ReportErr(
        Game::DescriptionStrings->at(Game::Language).bye_bye_msg);
#endif

    at_exit_message = Game::DescriptionStrings->at(Game::Language).bye_bye_msg;

    Terminal::Init();

    GameVariablesService::global_vars.Add(*Game::GlobalVariableDeclarations);

    GameLevelLogicProcessor::Init();

    is_inited = true;
  }
#ifdef PEP_DEBUG
  else {
    Terminal::ReportErr("Bad call to singleton Engine");
  }
#endif
}

// TODO: check for valid game logic loop
void pep::Engine::Play() {
  GameLevelLogicProcessor::GetSingleton().ProcessLevel(
      Game::DescriptionInfo->entry_point);
}