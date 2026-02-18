/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "testing.hpp"


// Global flags of compilation
// External libraries linkage
#define USE_SDL_IMAGE        true   // Library for load external images from disk
#define USE_NET              true   // Any of libraries for use with internet connection

// Number of active connections in internet part
#if USE_NET
#define MAX_CONNECTIONS 1
#endif
