//
// Created by vito on 1.11.20.
//

#include "text_world_object_processor.h"

#include <assets_loader.h>

#include <string>

#include "template_string_processing.h"
#include "to_string.h"
#include "utils/terminal.h"

void TextWorldObjectProcessor::Process(text_world_objects::Type two) {
  auto level = (*Game::Levels).at(current_level_id_);

  if (std::get_if<text_world_objects::Stand>(&two) != nullptr) {
    auto stand = std::get<text_world_objects::Stand>(two);

    auto asset_id = level.asset_string_ids.at(stand.msg_index);
    std::string message = Game::StringAssets->at(Game::Language).at(asset_id);

    FillTemplateString(message, stand.args_to_show);

    switch (stand.layout) {
      case text_world_objects::Stand::Layout::kFixedDefaultBordered:
        Terminal::PrintBorderedText('$', message);
        break;
      case text_world_objects::Stand::Layout::kPureText:
        Terminal::PrintText(message);
        break;
    };

    if (stand.is_input_expected) {
      Terminal::PressAnyKeyToContinue(
          Culture::strings.at(Game::Language).description_strings.input_tip);
    }
  }

  if (std::get_if<text_world_objects::DialogNaturalInput>(&two) != nullptr) {
    auto dialog = std::get<text_world_objects::DialogNaturalInput>(two);

    auto asset_tip_id = level.asset_string_ids.at(dialog.msg_tip_index);
    auto asset_bad_id = level.asset_string_ids.at(dialog.msg_bad_index);

    auto input_type = GameVariablesService::DefineType(dialog.input_result);

    if (input_type != VariableType::kNatural &&
        input_type != VariableType::kNatural0) {
      Terminal::ReportErr(
          ">>> OOPS!!! Unimplemented feature usage in Dialog input");
      Terminal::ReportErr("Level id: ");
      Terminal::ReportErr(std::to_string(current_level_id_));
    }

    auto input_result_variant_ptr =
        GameVariablesService::GetVariableLValueReferencePointer(
            dialog.input_result);

    auto* input_var = std::get<size_t*>(input_result_variant_ptr);

    auto interval =
        GameVariablesService::global_vars.getVariableNaturalInterval(
            dialog.natural_interval_display);

    auto message_tip = Game::StringAssets->at(Game::Language).at(asset_tip_id);

    if (dialog.is_using_templated_messages)
      FillTemplateString(message_tip, std::vector<game_var_name>{
                                          dialog.natural_interval_display});

    auto message_bad = Game::StringAssets->at(Game::Language).at(asset_bad_id);

    Terminal::InputValue(message_tip, message_bad, *input_var, interval.first,
                         interval.second);
  }
}

TextWorldObjectProcessor::TextWorldObjectProcessor(size_t current_level_id)
    : current_level_id_(current_level_id) {}
