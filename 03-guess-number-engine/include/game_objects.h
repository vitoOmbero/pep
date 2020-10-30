//
// Created by vito on 30.10.20.
//

#ifndef INC_03_GUESS_NUMBER_GAME_OBJECTS_H
#define INC_03_GUESS_NUMBER_GAME_OBJECTS_H

#include <variant>
#include <vector>

#include "game_variables.h"

namespace text_world_objects{

    using level_asset_id = size_t ;

    struct Dialog{
        game_var_t variable;
        level_asset_id msg_tip_id = 0;
        level_asset_id msg_bad_id = 1;
    };

    struct Stand{
        enum class Layout{
            kFixedDefaultBordered,
            kPureText,
        };

        std::vector<std::string> args;
        bool is_input_expected = true;
        Layout layout = Layout::kFixedDefaultBordered;
        level_asset_id msg_id = 0;
    };

    /*
     * Menu
     * Options
     * Table
     */

    using Type = std::variant<Dialog, Stand, std::monostate>;
}



#endif //INC_03_GUESS_NUMBER_GAME_OBJECTS_H
