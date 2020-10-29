#include <iostream>

#include <string>
#include <sstream>

#include "utils/terminal.h"

#include "game.h"
#include "engine.h"

void AtExit() {
    // TODO: should be moved to engine functionality + engine assets
    Terminal::PrintBorderedText('+', "Bye-bye!");
}

int main() {

    const int result = std::atexit(AtExit);

    if (result != 0)
    {
        // TODO: should be moved to engine functionality + engine assets
        Terminal::ReportErr("AtExit registration failed\n");
        return EXIT_FAILURE;
    }

    Game g_number;

    g_number.LoadAssets(Culture::kEn);

    g_number.Play();
    /* somehow
    Engine pep;

    pep.Init(g_number);

    pep.StartPlayFlow();
*/
    std::exit(EXIT_SUCCESS);
}
