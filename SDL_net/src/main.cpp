/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/libraries.hpp"
#include "internet/internet.hpp"

// Initialasing global objects in correct order
// Logger
#if (CHECK_ALL)
std::ofstream logFile{"log.txt"};
#endif

// All side libries
Libraries libraries{};

#if (USE_SDL_NET)
Internet internet{};
#endif

// Main function
int main(int argc, char ** argv) {
    if (argc == 1) {
        // Server type
        logAdditional("Started server, licening\n");
        // Getting string with full address of current host
        Uint16 port = internet.openServer();
        logAdditional("Current host: %s:%d", internet.getLocalhost(), port);

        // Getting any data
        while (true) {
            // Checking on getting new messages
            if (NET_Datagram* message = internet.getNewMessages()) {
                logAdditional("Get data with length %d: %s\n", message->buflen, message->buf);
                NET_DestroyDatagram(message);
                break;
            }
            // Sleeping for decrease load
            SDL_Delay(10);
        }
        internet.close();
    } else if (argc == 3) {
        // Starting random getting socket
        internet.openClient();

        // Client type
        Uint16 port = (Uint16)SDL_atoi(argv[2]);
        logAdditional("Started client, sending to %s:%d\n", argv[1], port);

        // Creating destination address, where try to send
        StringDestination destAddr{argv[1], port};
        // Trying send data to specified address
        char message[] = "Hello";
        Array<char> data{message, sizeof(message)};
        internet.sendFirst(destAddr, {ConnectionCode::Init, data});
    }
    
    return 0;
}
