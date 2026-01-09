#include <winsock2.h>
#include <iphlpapi.h>
#include <time.h>
#include <stdio.h>


// Global library, responsible for 
class Library {
 public:
    Library() {
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

// Class for setting destination (or source) address
class Address {
 private:
    sockaddr_in address;

 public:
    Address(const char* _host, u_short _port) {
        // The sockaddr_in structure specifies the address family,
        // IP address, and port for the socket that is being bound.
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(_host);
        address.sin_port = htons(_port);
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
        // Setting socket to broadcast
        bool t = true;
        setsockopt(sck, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(true));

        printf("Openned socket at port %d\n", ntohs(localAddress.sin_port));
    }
    ~Socket() {
        if (closesocket(sck) == SOCKET_ERROR) {
            printf("closesocket function failed with error %d\n", WSAGetLastError());
        }
    }
    void send(const char* _data, unsigned _size, const Address _dest) {
        if (sendto(sck, _data, _size, 0, _dest.getAddress(), sizeof(sockaddr_in)) < 0) {
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

void getLocalName1() {
    char name[100];
    gethostname(name, sizeof(name));

    printf("Name: %s\n", name);
}

void getLocalName2(SOCKET socket) {
    // Getting peer name
    char name[100];
    sockaddr_in addr;
    int size = sizeof(addr);
    getpeername(socket, (sockaddr*)&addr, &size);
    printf("Peer parameters: %s, %d\n", addr.sin_addr, size);
}

void getLocalName3() {
    char buffer[10000];
    PIP_ADAPTER_ADDRESSES addresses = (PIP_ADAPTER_ADDRESSES)buffer;
    unsigned long length = sizeof(buffer);

    u_long dwRetVal = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, 
        NULL, addresses, &length);

    // Searching for local address from linked list
    while (addresses) {
        PIP_ADAPTER_UNICAST_ADDRESS pUnicast = addresses->FirstUnicastAddress;

        while (pUnicast != NULL) {
            sockaddr_in* sa_in = (sockaddr_in*)pUnicast->Address.lpSockaddr;

            char* ipStr = inet_ntoa(sa_in->sin_addr);
            printf("Address: %s:%d\n", ipStr, sa_in->sin_port);

            // Исключаем loopback
            if (strcmp(ipStr, "127.0.0.1")) {
                // Записываем полученный адресс
                printf("Select this\n");
                return;
            }
            
            pUnicast = pUnicast->Next;
        }
        
        addresses = addresses->Next;
    }
}

Library lib;

int main(int argc, char ** argv) {
    // Creating global recieving socket (with local address)
    Socket socket{8000};
    getLocalName1();
    //getLocalName2(socket);
    getLocalName3();

    if (argc == 1) {
        // Server type
        printf("Started server, licening\n");
        // Getting any data
        while (true) {
            // Checking on getting new messages
            if (socket.recieve()) {
                break;
            }
            // Sleeping for decrease load
            Sleep(10);
        }
    } else if (argc == 3) {
        // Client type
        u_short port = (u_short)atoi(argv[2]);
        printf("Started client, sending to %s:%d\n", argv[1], port);

        // Creating destination address, where try to send
        Address destAddr{argv[1], port};

        char buffer[] = "Hello";
        socket.send(buffer, sizeof(buffer), destAddr);
    }
    
    return 0;
}
