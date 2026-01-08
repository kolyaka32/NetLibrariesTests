/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */


#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include "libraries.hpp"
#include "exceptions.hpp"


Libraries::Libraries() {
    // Load depend on testing
    #if (CHECK_CORRECTION)
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }
    // Intialasing internet library
    #if (USE_SDL_NET)
    if (!NET_Init()) {
        throw LibararyLoadException("Couldn't initialase internet library: " + std::string(SDL_GetError()));
    }
    #endif
    logAdditional("Libraries load correctly");
    #else  // (CHECK_CORRECTION)
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #if (USE_SDL_NET)
    NET_Init();
    #endif
    #endif  // (CHECK_CORRECTION)
}

Libraries::~Libraries() noexcept {
    // Closing internet library
    #if (USE_SDL_NET)
    NET_Quit();
    #endif

    // Closing main SDL library
    SDL_Quit();
}
