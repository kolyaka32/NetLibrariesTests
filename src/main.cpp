#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    //-----------------------------------------
    // Declare and initialize variables
    WSADATA wsaData = {0};
    //int iResult = 0;

    SOCKET sock = INVALID_SOCKET;
    int iFamily = AF_UNSPEC;
    int iType = 0;
    int iProtocol = 0;

    // Validate the parameters
    if (argc != 4) {
        printf("usage: %s <addressfamily> <type> <protocol>\n", argv[0]);
        printf("socket opens a socket for the specified family, type, & protocol\n");
        printf("%ws example usage\n", argv[0]);
        printf("   %ws 0 2 17\n", argv[0]);
        printf("   where AF_UNSPEC=0 SOCK_DGRAM=2 IPPROTO_UDP=17\n", argv[0]);
        return 1;
    }

    iFamily = atoi(argv[1]);
    iType = atoi(argv[2]);
    iProtocol = atoi(argv[3]);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    printf("Calling socket with following parameters:\n");
    printf("  Address Family = ");
    switch (iFamily) {
    case AF_UNSPEC:
        printf("Unspecified");
        break;
    case AF_INET:
        printf("AF_INET (IPv4)");
        break;
    case AF_INET6:
        printf("AF_INET6 (IPv6)");
        break;
    case AF_NETBIOS:
        printf("AF_NETBIOS (NetBIOS)");
        break;
    case AF_BTH:
        printf("AF_BTH (Bluetooth)");
        break;
    default:
        printf("Other");
        break;
    }
    printf(" (%d)\n", iFamily);

    printf("  Socket type = ");
    switch (iType) {
    case 0:
        printf("Unspecified");
        break;
    case SOCK_STREAM:
        printf("SOCK_STREAM (stream)");
        break;
    case SOCK_DGRAM:
        printf("SOCK_DGRAM (datagram)");
        break;
    case SOCK_RAW:
        printf("SOCK_RAW (raw)");
        break;
    case SOCK_RDM:
        printf("SOCK_RDM (reliable message datagram)");
        break;
    case SOCK_SEQPACKET:
        printf("SOCK_SEQPACKET (pseudo-stream packet)");
        break;
    default:
        printf("Other");
        break;
    }
    printf(" (%d)\n", iType);

    printf("  Protocol = %d = ", iProtocol);
    switch (iProtocol) {
    case 0:
        printf("Unspecified");
        break;
    case IPPROTO_ICMP:
        printf("IPPROTO_ICMP (ICMP)");
        break;
    case IPPROTO_IGMP:
        printf("IPPROTO_IGMP (IGMP)");
        break;
    case IPPROTO_TCP:
        printf("IPPROTO_TCP (TCP)");
        break;
    case IPPROTO_UDP:
        printf("IPPROTO_UDP (UDP)");
        break;
    case IPPROTO_ICMPV6:
        printf("IPPROTO_ICMPV6 (ICMP Version 6)");
        break;
    default:
        printf("Other");
        break;
    }
    printf(" (%d)\n", iProtocol);

    sock = socket(iFamily, iType, iProtocol);
    if (sock == INVALID_SOCKET) 
        printf("socket function failed with error = %d\n", WSAGetLastError() );
    else {
        printf("socket function succeeded\n");

        // Close the socket to release the resources associated
        // Normally an application calls shutdown() before closesocket 
        //   to  disables sends or receives on a socket first
        // This isn't needed in this simple sample
        if (closesocket(sock) == SOCKET_ERROR) {
            wprintf(L"closesocket failed with error = %d\n", WSAGetLastError() );
            WSACleanup();
            return 1;
        }    
    }

    WSACleanup();

    return 0;
}
