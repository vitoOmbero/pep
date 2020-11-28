//
// Created by vito on 2.11.20.
//

#ifndef INC_03_GUESS_NUMBER_TEMPLATE_STRING_PROCESSING_H
#define INC_03_GUESS_NUMBER_TEMPLATE_STRING_PROCESSING_H

#include <algorithm>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/find_format.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>

#include "game_variables_service.h"
#include "utils/terminal.h"

inline static const size_t kDefaultReserve{10};
inline void FillTemplateString(std::string& template_string,
                               const std::vector<std::string>& var_names) {
  if (var_names.empty()) return;

#ifdef PEP_DEBUG
    // TODO: string asset validation
#endif
  using namespace boost;

  iterator_range<std::string::iterator> range =
      find_first(template_string, std::string("<var>"));

  if (range.empty()) {
    return;
  }

  // TODO: work with local variables (?)

  std::for_each(var_names.begin(), var_names.end(),
                [&template_string](const std::string& arg) {
                  replace_all(template_string, arg,
                              GameVariablesService::GetValueAsString(arg));
                });

  replace_all(template_string, "<var>", "");
  replace_all(template_string, "</var>", "");
}
#endif  // INC_03_GUESS_NUMBER_TEMPLATE_STRING_PROCESSING_H
