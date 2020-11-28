#ifndef INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H
#define INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "engine/pep.h"

namespace VisualScenes::Assets {

// TODO: string assets in files
// TODO: string asset files reader

inline const std::vector<std::string> eng_str_assets{
    // NOLINT(cert-err58-cpp)
    // NOLINT(cert-err58-cpp)
    "Welcome to the <var>@@game_title</var>!",
    "This is level with triangle",
    "This is level with quad",
    "Press W to change rendering mode",
    "Press Up and Down arrow keys to switch the color",
    "Press Left and Right arrow keys to switch the level",
    "Mouse swipes should work too.",
    "Touch swipes should work too.",
    "<var>@@game_title</var> finished!",
    "This is level with texture",       //9
    "This is level with sprite"
    // "Press O and P to switch input modes",
    // "Gestures should work too."
    // "Input mode switched to Choose Level",
    // "Input mode switched to Move Texture",
    };

inline const std::vector<std::string> ru_str_assets{
    // NOLINT(cert-err58-cpp)
    // NOLINT(cert-err58-cpp)
    "Добро пожаловать в <var>@@game_title</var>!",
    "Это уровень с треугольником",
    "Это уровень с квадратом",
    "Нажмите W для смены режима отрисовки",
    "Нажмите Вверх и Вниз клавишу стрелки для переключения цвета",
    "Нажмите Вправо и Влево клавишу стрелки для переключения уровня",
    "Свайпы мышью тоже должны работать",
    "Свайпы на тач-экране тоже должны работать",
    "<var>@@game_title</var> окончено!",
    "Это уровень с текстурой",          //9
    "Это уровень со спрайтом"
        // "Нажмите O и P для переключения режмов ввода",
        // "Жесты тоже должны работать"
        // "Режим ввода переключен на Выбор Уровня",
        // "Режим ввода переключен на Перемещение Текустуры",
    };

inline const std::unordered_map<Culture::Language,
                                std::vector<std::string>>
    game_assets_strings = {  // NOLINT(cert-err58-cpp)
        {Culture::kEn, eng_str_assets},
        {Culture::kRu, ru_str_assets}};

inline const TexturePackMap
    game_assets_texture_packs = {
        {0, {{"assets/images/backgrounds/spr_fon_01_0.png"}}}
};



#define EXPATH "assets/images/explosion/"

inline static const SpriteMultiImage explosion {
    EXPATH"spr_explosion_0.png",
    EXPATH"spr_explosion_1.png",
    EXPATH"spr_explosion_2.png",
    EXPATH"spr_explosion_3.png",
    EXPATH"spr_explosion_4.png",
    EXPATH"spr_explosion_5.png",
    EXPATH"spr_explosion_6.png",
    EXPATH"spr_explosion_7.png",
    EXPATH"spr_explosion_8.png",
    EXPATH"spr_explosion_9.png",
    EXPATH"spr_explosion_10.png",
    EXPATH"spr_explosion_11.png",
    EXPATH"spr_explosion_12.png",
    EXPATH"spr_explosion_13.png",
    EXPATH"spr_explosion_14.png",
    EXPATH"spr_explosion_15.png",
    EXPATH"spr_explosion_16.png",
};


#define EXPATH "assets/images/testplayer/"

inline static const SpriteMultiImage player {
        EXPATH"spr_player_0.png",
        EXPATH"spr_player_1.png",
        EXPATH"spr_player_2.png",
        EXPATH"spr_player_3.png",
        EXPATH"spr_player_4.png",
        EXPATH"spr_player_5.png",
        EXPATH"spr_player_6.png",
        EXPATH"spr_player_7.png",
        EXPATH"spr_player_8.png",
        EXPATH"spr_player_9.png",
        EXPATH"spr_player_10.png",
        EXPATH"spr_player_11.png",
        EXPATH"spr_player_12.png",
        EXPATH"spr_player_13.png",
        EXPATH"spr_player_14.png",
        EXPATH"spr_player_15.png",
};

inline static const std::vector<SpriteMultiImage> game_sprite_multi_images {
    explosion,
    player
};

}  // namespace GuessNumber::Assets

#endif  // INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H