//
// Created by vito on 29.10.20.
//

#include "game.h"

#include <random>
#include <cmath>

#include "utils/g_number_assets.h"
#include "utils/g_number_metainfo.h"
#include "utils/terminal.h"

size_t GetUniformRandomNaturalNumber(size_t max) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<size_t> uniform_dist(1, max);

    return uniform_dist(e1);
}

const std::string &Game::getTitle() const {
    return title_;
}

const Version &Game::getVer() const {
    return ver_;
}

void Game::LoadAssets(Culture::Language lang) {
    lang_ = lang;
    title_ = GuessNumber::game_description_strings.at(lang).title;
    default_filler = GuessNumber::game_description_strings.at(lang).default_filler.at(0);
}

char Game::getDefaultFiller() const {
    return default_filler;
}

Culture::Language Game::getLang() const {
    return lang_;
}

void Game::Play() const {
    std::ostringstream oss;
    oss << GuessNumber::Assets::game_assets_strings.at(getLang())[0] << getTitle() << "!";
    std::string game_welcome = oss.str();

    Terminal::Init();
    Terminal::PrintBorderedText(getDefaultFiller(), game_welcome);
    Terminal::PrintBorderedText('=', ToString(getVer(), getLang()));

    Terminal::PressAnyKeyToContinue(Culture::strings.at(getLang()).description_strings.input_tip);

    // Setup game difficulty

    // Setup low-level definitions
    const size_t kSecretNumberMax = 100500;

    // Setup high-level definitions
    size_t difficulty_level;
    Terminal::InputValue(
            GuessNumber::Assets::game_assets_strings.at(getLang())[1],
            GuessNumber::Assets::game_assets_strings.at(getLang())[2],
            difficulty_level, 1, 3);

    size_t attempts_max;

    if (difficulty_level < 3) {
        attempts_max = static_cast<size_t>(log2(static_cast<double>(kSecretNumberMax)));
        if (difficulty_level == 1) {
            Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[3], kSecretNumberMax);
        }
    } else {
        attempts_max = log2(static_cast<double>(kSecretNumberMax)) / 3 * 2;
    }

    Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[4], attempts_max);
    Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[5]);

    size_t secret_number = GetUniformRandomNaturalNumber(kSecretNumberMax);

#ifdef PEP_VERBOSE_GAME_LOGIC
    oss.str("");
    oss.clear();
    oss << GuessNumber::Assets::game_assets_strings.at(getLang())[6] << std::to_string(secret_number);
    Terminal::PrintBorderedText('$', oss.str());
#endif

    size_t attempt_counter = 0;

    bool is_not_finished = true;

    while (is_not_finished) {
        size_t num;
        Terminal::InputValue(GuessNumber::Assets::game_assets_strings.at(getLang())[7],
                             GuessNumber::Assets::game_assets_strings.at(getLang())[8],
                             num, 1, kSecretNumberMax);

        if (num < secret_number) {
            Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[9]);
            ++attempt_counter;
        }

        if (num > secret_number) {
            Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[10]);
            ++attempt_counter;
        }

        if (num == secret_number) {
            Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[11], num, "!");
            is_not_finished = false;
        }

        if (attempt_counter < attempts_max) {
            Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[12],
                                attempts_max - attempt_counter, " ");
        } else {
            Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[13]);
            is_not_finished = false;
        }
    }

    Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[14]);
    Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[15], secret_number);
    Terminal::ReportVal(GuessNumber::Assets::game_assets_strings.at(getLang())[16], attempt_counter);

    if (attempt_counter < attempts_max)
        Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[17]);
    else
        Terminal::ReportMsg(GuessNumber::Assets::game_assets_strings.at(getLang())[18]);
}
