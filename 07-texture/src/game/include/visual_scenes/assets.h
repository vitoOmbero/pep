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
    "This is level with texture",
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
    "Это уровень с текстурой",
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

}  // namespace GuessNumber::Assets

#endif  // INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H