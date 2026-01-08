/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "testing.hpp"


// Global flags of compilation
// External libraries linkage
#define USE_SDL_IMAGE        true   // Library for load external images from disk
#define USE_SDL_NET          true   // Library for internet connection by UDP/TCP


// Number of active connections in internet part
#if USE_SDL_NET
#define MAX_CONNECTIONS 1
#endif
