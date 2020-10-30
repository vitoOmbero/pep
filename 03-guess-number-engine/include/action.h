//
// Created by vito on 29.10.20.
//

#ifndef INC_03_GUESS_NUMBER_ACTION_H
#define INC_03_GUESS_NUMBER_ACTION_H

#include <variant>

namespace action {
    using procedure = void (*)(uint32_t &);
    using function = uint32_t(*)(uint32_t);
    using action = void (*)();
}

using action_t = std::variant<action::procedure, action::function, action::action, std::monostate>;

#endif //INC_03_GUESS_NUMBER_ACTION_H
