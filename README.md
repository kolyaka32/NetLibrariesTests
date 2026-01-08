# C++ internet libraries test subproject

That is small test subproject for test net libraries, its opportinities and compilation.
At all in future can be croos-platform sublibrary for net connection.
Try to implement code in OOP-style, C++ 11/14 standart.
Use CMake for correct compilation and linkage of libraries.

## Variants

At this moment tried:
1. [SDL_net](https://github.com/libsdl-org/SDL_net) (2.0, 3.0): Works properly, cross-platform, but not allow to send broadcast messages. Also had not full control over all processes and use mostly heap memory. Realistion in "SDL_net" directory;
2. [Winsock2.h](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/) (with iphlpapi.h): Works also properly, allows to broadcast messages, low-level. Work only on windows. Realistion in "winsock" directory;
3. [Socket.h](https://www.opennet.ru/man.shtml?topic=socket.h): Not tested yet. Unix-system only. (Will be used with winsock2.h)
