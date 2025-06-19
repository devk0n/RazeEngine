#include "Engine.h"
#include <iostream>
#include <stdexcept>

int main() {
    Raze::Engine engine;

    try {
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

