//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H
#define INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H

#include <string>
#include <unordered_map>
#include <vector>

#include "engine_assets.h"

namespace GuessNumber::Assets {

inline const std::vector<std::string> eng_str_assets{
    // NOLINT(cert-err58-cpp)
    "Welcome to the <var>@@game_title</var>!",
    "Choose difficulty level <var>@diff_interval</var>:",
    "This value shall not pass!",
    "Max number: <var>@number_max</var>",
    "Max attempts: <var>@attempts_max</var>",
    "Game started! ",  // 5
    "Randomly-chosen number: <var>@secret_number</var>",
    "?: ",
    "!: incorrect input...",
    "Secret number is bigger",
    "Secret number is smaller",  // 10
    "Yes, secret number is <var>@secret_number</var>!",
    "You have <var>@attempts_left</var> attempts.",
    "You have no attempts.",
    "Game finished.",
    "Secret number: <var>@secret_number</var>",  // 15
    "Attempts: <var>@attempt_counter</var>",
    "Number was guessed.",
    "Number was not guessed."};

inline const std::vector<std::string> ru_str_assets{
    // NOLINT(cert-err58-cpp)
    "Добро пожаловать в <var>@@game_title</var>!",
    "Выберитк уровень сложности <var>@diff_interval</var>:",
    "Это значение не подходит!",
    "Макс. число: <var>@number_max</var>",
    "Макс. попыток: <var>@attempts_max</var>",
    "Игра началась! ",
    "Секр.число <var>@secret_number</var>",
    "?: ",
    "!: некорректный ввод...",
    "Секретное число больше",
    "Секретное число меньше",
    "Верно, секретное число <var>@secret_number</var>!",
    "Осталось <var>@attempts_left</var> попыток.",
    "У вас нет больше попыток.",
    "Игра окончена.",
    "Секретное число: <var>@secret_number</var>",
    "Попыток: <var>@attempt_counter</var>",
    "Число было отгадано.",
    "Число не было отгадано."};

inline const std::unordered_map<Culture::Language,
                                std::vector<std::string>>
    game_assets_strings = {  // NOLINT(cert-err58-cpp)
        {Culture::kEn, eng_str_assets},
        {Culture::kRu, ru_str_assets}};
}  // namespace GuessNumber::Assets

#endif  // INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H