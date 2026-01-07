#include <winsock2.h>
#include "time.h"
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
    sockaddr_in localAddress;
    SOCKET sck = INVALID_SOCKET;

 public:
    Socket(u_short _port) {
        // Create a SOCKET for listening for incoming connection requests.
        sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sck == INVALID_SOCKET) {
            printf("socket function failed with error: %ld\n", WSAGetLastError());
        }
        // Setting local address
        localAddress.sin_family = AF_INET;
        localAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        localAddress.sin_port = htons(_port);
        // Setting random seed from time
        srand(time(0));
        // Finding avaliable port
        // Setting socket to send from created local host (as back address)
        while (bind(sck, (SOCKADDR*)&localAddress, sizeof(localAddress)) == SOCKET_ERROR) {
            if (WSAGetLastError() == 10048) {
                // Trying find another port
                localAddress.sin_port = htons(rand() % 10000);
            } else {
                // Error
                printf("bind function failed with error %d\n", WSAGetLastError());
            }
        }
        printf("Openned socket at port %d\n", ntohs(localAddress.sin_port));
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
    bool recieve() {
        sockaddr_in fromAddr;
        char buffer[100];
        int size = sizeof(sockaddr_in);
        if (recvfrom(sck, buffer, sizeof(buffer), 0, (SOCKADDR*)&fromAddr, &size) < 0) {
            printf("can't recieve data\n");
        } else {
            printf("Get data with length %d: %s\n", size, buffer);
            return true;
        }
        return false;
    }
};

Library lib;

int main(int argc, char ** argv) {
    

    if (argc == 1) {
        // Server type
        Socket socket{8000};

        // Getting any data
        while (true) {
            if (socket.recieve()) {
                break;
            }
            Sleep(10);
        }
    } else if (argc == 3) {
        // Client type
        Socket socket{8000};
        Address destAddr{argv[1], (u_short)atoi(argv[2])};

        char buffer[] = "Hello";
        socket.send(buffer, sizeof(buffer), destAddr);
    }
    
    return 0;
}
