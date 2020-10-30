//
// Created by vito on 29.10.20.
//

#ifndef INC_01_GUESS_NUMBER_PROTO_GAME_H
#define INC_01_GUESS_NUMBER_PROTO_GAME_H

#include <string>
#include <unordered_map>

// TODO: move to ... game loader(?)
#include "utils/g_number_metainfo.h"

#include "version.h"
#include "to_string.h"

class Game {
public:
    [[nodiscard]] const std::string &getTitle() const;
    [[nodiscard]] const Version &getVer() const;
    [[nodiscard]] char getDefaultFiller() const;
    [[nodiscard]] Culture::Language getLang() const;

    void LoadAssets(Culture::Language lang);

    void Play() const;

private:
    Version ver_ = GuessNumber::gdi.version;
    std::string title_;
    char default_filler;
    Culture::Language lang_;
};


#endif //INC_01_GUESS_NUMBER_PROTO_GAME_H
