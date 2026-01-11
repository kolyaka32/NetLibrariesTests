/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */


#include <SDL3/SDL.h>
#include "libraries.hpp"
#include "../internet/library.hpp"
#include "exceptions.hpp"


Libraries::Libraries() {
    // Load depend on testing
    #if (CHECK_CORRECTION)
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }
    // Intialasing internet library
    #if (USE_NET)
    if (initNet()) {
        throw LibararyLoadException("Couldn't initialase internet library: " + std::string(SDL_GetError()));
    }
    #endif
    logAdditional("Libraries load correctly");
    #else  // (CHECK_CORRECTION)
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #if (USE_NET)
    initNet();
    #endif
    #endif  // (CHECK_CORRECTION)
}

Libraries::~Libraries() noexcept {
    // Closing internet library
    #if (USE_NET)
    closeNet();
    #endif

    // Closing main SDL library
    SDL_Quit();
}
