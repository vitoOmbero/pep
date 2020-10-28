#include <iostream>
#include <random>
#include <cmath>

size_t SetSecretNumber(size_t max) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<size_t> uniform_dist(1, max);

    return uniform_dist(e1);
}

int main() {
    std::cout << "Intro, hello!" << std::endl;

    // Setup game difficulty

    // Setup low-level definitions
    const size_t kTriesMax = 5;
    const size_t kSecretNumberMax = 100500;

    // Setup high-level definitions
    std::cout << "Choose difficulty level (1..3): " << std::endl;
    size_t difficulty_level;
    std::cin >> difficulty_level;

    size_t tries_max = 0;

    if (difficulty_level < 2) {
        tries_max = log2(static_cast<double>(kSecretNumberMax));
        std::cout << "Max number: " << kSecretNumberMax <<std::endl;
    } else if (difficulty_level == 2) {
        tries_max = log2(static_cast<double>(kSecretNumberMax));
    } else {
        tries_max = log2(static_cast<double>(kSecretNumberMax))/3*2;
    }

    std::cout << "Max tries: " << tries_max << std::endl;
    std::cout << "Game started! " << std::endl;

    size_t secret_number = SetSecretNumber(kSecretNumberMax);

#ifdef PEP_VERBOSE_GAME_LOGIC
    std::cout << "Randomly-chosen number: " << secret_number << '\n';
#endif

    size_t try_counter = 0;

    bool is_not_finished = true;

    while (is_not_finished){
        size_t num;
        std::cout << "?: ";
        std::cin >> num;

        if (num < secret_number){
            std:: cout << "Secret number is bigger" << std::endl;
            ++try_counter;
        }

        if (num > secret_number){
            std:: cout << "Secret number is smaller" << std::endl;
            ++try_counter;
        }

        if (num == secret_number){
            std:: cout << "Yes, secret number is " << num << "!" << std::endl;
            is_not_finished = false;
        }

        if (try_counter < tries_max){
            std::cout << "You have " << tries_max-try_counter << " tries." << std::endl;
        }
    }

    std::cout << "Game finished." << std::endl;
    std::cout << "Secret number: " << secret_number << std::endl;
    std::cout << "Tries: " << try_counter << std::endl;

    if (try_counter < tries_max)
        std::cout << "Number was guessed." << std::endl;
    else
        std::cout << "Number was not guessed." << std::endl;

    std::cout << "Outro, bb!" << std::endl;
    return EXIT_SUCCESS;
}
