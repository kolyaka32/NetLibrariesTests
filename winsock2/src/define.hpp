/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "testing.hpp"


// Global flags of compilation
// External libraries linkage
#define USE_SDL_IMAGE        true   // Library for load external images from disk

#define USE_WINSOCK          true   // Library for internet connection by UDP/TCP


// Number of active connections in internet part
#if USE_WINSOCK
#define MAX_CONNECTIONS 1
#endif
