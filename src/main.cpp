#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


class Library {
private:
    /* data */
public:
    Library(/* args */) {
        // Initialize Winsock
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
            printf("WSAStartup() failed\n");
        }
    }
    ~Library() {
        if (WSACleanup() < 0) {
            printf("Can't cleanup\n");
        }
    }
};

class Address {
private:
    sockaddr_in address;
public:
    Address(const char* _host, u_short _port) {
        //----------------------
        // The sockaddr_in structure specifies the address family,
        // IP address, and port for the socket that is being bound.
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(_host);
        address.sin_port = htons(_port);
    }
    ~Address() {

    }
    const SOCKADDR* getAddress() const {
        return (SOCKADDR*)&address;
    }
};


class Socket {
private:
    SOCKET sck = INVALID_SOCKET;
public:
    Socket(Address localAddress) {
        //----------------------
        // Create a SOCKET for listening for incoming connection requests.
        sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sck == INVALID_SOCKET) {
            printf("socket function failed with error: %ld\n", WSAGetLastError());
        }
        // Setting socket to send from local host (as back address)
        if (bind(sck, localAddress.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
            printf("bind function failed with error %d\n", WSAGetLastError());
        }
    }
    ~Socket() {
        if (closesocket(sck) == SOCKET_ERROR) {
            printf("closesocket function failed with error %d\n", WSAGetLastError());
        }
    }
    void send(const char* _data, unsigned _size, const Address _dest) {
        const int flag = 0;
        if (sendto(sck, _data, _size, flag, _dest.getAddress(), sizeof(sockaddr_in)) < 0) {
            printf("Can't send data %d\n", WSAGetLastError());
        } else {
            printf("Send sucsesfull: %s\n", _data);
        }
    }
    void recieve() {
        sockaddr_in fromAddr;
        char buffer[100];
        int size = sizeof(sockaddr_in);
        if (recvfrom(sck, buffer, sizeof(buffer), 0, (SOCKADDR*)&fromAddr, &size) < 0) {
            printf("can't recieve data\n");
        }
    }
};

Library lib;

int main() {
    Address localAddr{"127.0.0.1", 8794};

    char buffer[] = "Hello";

    Socket socket{localAddr};

    Address destAddr{"127.0.0.1", 8000};

    socket.send(buffer, sizeof(buffer), destAddr);
    return 0;
}
