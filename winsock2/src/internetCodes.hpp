/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Codes for send/recieve in internet messages
enum class ConnectionCode {
    // System codes
    Null,     // Code of absence of new messages
    Init,     // Code for initialise connection
    Quit,     // Code for break connection (not need aprove)
    Confirm,  // Code for confirm, that importane message was delivered (with number of message)
    ApplyConnection,  // Code of confirmation of continued connection

    // Game codes
    // Global
    GameTurn,     // Code of normal game turn with it options
    // Server-side
    GameNew,      // Code of sending new field
    // GameRestart,  // Code of restart game with options of new game (field, turn)
};

// Basic connecting port
const unsigned short basePort = 8000;
