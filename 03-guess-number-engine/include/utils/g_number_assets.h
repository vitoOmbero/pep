//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H
#define INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H

#include <string>
#include <vector>
#include <unordered_map>

#include "engine_assets.h"

namespace GuessNumber::Assets {

    inline static const std::vector<std::string> eng_str_assets{ // NOLINT(cert-err58-cpp)
            "Welcome to the @@<game_title>!",
            "Choose difficulty level @<diff_interval>:",
            "This value shall not pass!",
            "Max number: @<number_max>",
            "Max attempts: @<attempts_max>",
            "Game started! ", // 5
            "Randomly-chosen number: @<secret_number>",
            "?: ",
            "!: incorrect input...",
            "Secret number is bigger",
            "Secret number is smaller", // 10
            "Yes, secret number is @<secret_number>!",
            "You have @<attempts_left> attempts.",
            "You have no attempts.",
            "Game finished.",
            "Secret number: @<secret_number>", // 15
            "Attempts: @<attempt_counter>",
            "Number was guessed.",
            "Number was not guessed."
    };

    inline static const std::vector<std::string> ru_str_assets{ // NOLINT(cert-err58-cpp)
            "Добро пожаловать в @@<game_title>!",
            "Выберитк уровень сложности @<diff_interval>:",
            "Это значение не подходит!",
            "Макс. число: @<number_max>",
            "Макс. попыток: @<attempts_max>",
            "Игра началась! ",
            "Секр.число @<secret_number>",
            "?: ",
            "!: некорректный ввод...",
            "Секретное число больше",
            "Секретное число меньше",
            "Верно, секретное число @<secret_number>!",
            "Осталось @<attempts_left> попыток.",
            "У вас нет больше попыток.",
            "Игра окончена.",
            "Секретное число: @<secret_number>",
            "Попыток: @<attempt_counter>",
            "Число было отгадано.",
            "Число не было отгадано."
    };

    inline static const std::unordered_map<Culture::Language, std::vector<std::string>> game_assets_strings = { // NOLINT(cert-err58-cpp)
            {Culture::kEn, eng_str_assets},
            {Culture::kRu, ru_str_assets}
    };
}

#endif //INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H