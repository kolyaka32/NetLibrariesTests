

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


SOCKET ListenSocket = INVALID_SOCKET;

int close() {
    if (closesocket(ListenSocket) == SOCKET_ERROR) {
        wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
}

int init(const char* _host, u_short _port) {
    //----------------------
    // Initialize Winsock
    WSADATA wsaData;

    int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != NO_ERROR) {
        wprintf(L"WSAStartup() failed with error: %d\n", startupResult);
        return 1;
    }
    //----------------------
    // Create a SOCKET for listening for incoming connection requests.
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(_host);
    service.sin_port = htons(_port);

    int bindResult = bind(ListenSocket, (SOCKADDR *) &service, sizeof(service));
    if (bindResult == SOCKET_ERROR) {
        wprintf(L"bind function failed with error %d\n", WSAGetLastError());
        close();
        return 1;
    }
}



int main() {
    init("127.0.0.1", 27015);

    //----------------------
    // Listen for incoming connection requests 
    // on the created socket
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
        wprintf(L"listen function failed with error: %d\n", WSAGetLastError());

    wprintf(L"Listening on socket...\n");

    close();

    return 0;
}
