//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H
#define INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <string>
#include <vector>
#include <unordered_map>

#include "to_string.h"

namespace GuessNumberAssets {

    inline static const std::unordered_map<Culture::Language, GameInstanceStrings> game_description_strings = {
            {Culture::kEn, {"Guess The FNumber", "$"}},
            {Culture::kRu, {"Угадай БЧисло",     "@"}}
    };

    inline static const Version version {0,1,1};

    inline static  const std::vector<std::string> eng_str_assets{
            //"Welcome to the @<title>!",
            "Welcome to the ",
            "Choose difficulty level (1..3):",
            "This value shall not pass!",
            "Max number: ",
            "Max attempts: ",
            "Game started! ", // 5
            "Randomly-chosen number: ",
            "?: ",
            "!: incorrect input...",
            "Secret number is bigger",
            "Secret number is smaller", // 10
            //"Yes, secret number is @<value_n0>!",
            "Yes, secret number is ",
            //"You have @<value_n0> attempts.",
            "attempts left ",
            "You have no attempts.",
            "Game finished.",
            "Secret number: ", // 15
            "attempts: ",
            "Number was guessed.",
            "Number was not guessed."
    };

    inline static const std::vector<std::string> ru_str_assets{
            //"Добро пожаловать в @<title>!",
            "Добро пожаловать в ",
            "Выберитк уровень сложности (1..3):",
            "Это значение не подходит!",
            "Макс. число: ",
            "Макс. попыток: ",
            "Игра началась! ",
            "Секр.число ",
            "?: ",
            "!: некорректный ввод...",
            "Секретное число больше",
            "Секретное число меньше",
            //"Верно, секретное число @<value_n0>!",
            "Верно, секретное число ",
            //"Осталось @<value_n0> попыток.",
            "Осталось попыток ",
            "У вас нет больше попыток.",
            "Игра окончена.",
            "Секретное число: ",
            "Поптыок: ",
            "Число было отгадано.",
            "Число не было отгадано."
    };

    inline static const std::unordered_map<Culture::Language, std::vector<std::string>> game_stage_strings = {
            {Culture::kEn, eng_str_assets},
            {Culture::kRu, ru_str_assets}
    };
}

#pragma clang diagnostic pop

#endif //INC_01_GUESS_NUMBER_PROTO_G_NUMBER_ASSETS_H

